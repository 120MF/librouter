#include "ConcurrentHashmap.h"

#include <mutex>
#include <stdexcept>

template <typename Key, typename Value>
ConcurrentHashmap<Key, Value>::ConcurrentHashmap(std::function<uint32_t(Key)> hashFunction)
{
    Hashtable = new ConcurrentBucket<Key, Value>*[size];
    for (uint32_t i = 0; i < size; i++)
    {
        Hashtable[i] = nullptr;
    }
}

template <typename Key, typename Value>
ConcurrentHashmap<Key, Value>::~ConcurrentHashmap()
{
    for (uint32_t i = 0; i < size; i++)
    {
        delete Hashtable[i];
    }
    delete[] Hashtable;
}

template <typename Key, typename Value>
bool ConcurrentHashmap<Key, Value>::set(Key key, Value value)
{
    uint32_t used_buckets_ = used_buckets.load(std::memory_order_acquire);
    if (used_buckets_ + 1 > size * load_factor) resize();
    const uint32_t val = hashCompute(key);
    uint32_t start = val % size;
    const uint32_t end = (start > 0) ? ((start - 1) % size) : size - 1;

    bool has_key = false;
    while (start != end)
    {
        if (Hashtable[start] == nullptr) break;
        if (Hashtable[start]->key.load(std::memory_order_acquire) == key)
        {
            has_key = true;
            break;
        }
        start = (start + 1) % size;
    }
    if (start == end) return false;
    if (has_key) delete Hashtable[start];
    else ++used_buckets_;
    used_buckets.store(used_buckets_, std::memory_order_release);
    Hashtable[start] = new ConcurrentBucket<Key, Value>(key, value);
    return true;
}

template <typename Key, typename Value>
Value ConcurrentHashmap<Key, Value>::get(const Key& key)
{
    std::shared_lock<std::shared_mutex> lock(resize_mutex);

    if (used_buckets.load(std::memory_order_relaxed) == 0)
        throw std::invalid_argument(
            "Can't find key on an empty map.");

    const uint32_t val = hashCompute(key);
    uint32_t start = val % size;
    const uint32_t end = (start > 0) ? ((start - 1) % size) : size - 1;
    while (start != end)
    {
        if (Hashtable[start] != nullptr && Hashtable[start]->key.load(std::memory_order_acquire) == key)
        {
            return Hashtable[start]->value.load(std::memory_order_acquire);
        }
        start = (start + 1) % size;
    }
    throw std::invalid_argument("Key not found.");
}

template <typename Key, typename Value>
void ConcurrentHashmap<Key, Value>::erase(const Key& key)
{
    uint32_t used_buckets_ = used_buckets.load(std::memory_order_acquire);
    if (used_buckets_ == 0) throw std::invalid_argument("Can't erase key on an empty map.");

    const uint32_t val = hashCompute(key);
    uint32_t start = val % size;
    const uint32_t end = (start > 0) ? ((start - 1) % size) : size - 1;
    while (start != end)
    {
        if (Hashtable[start] != nullptr && Hashtable[start]->key.load(std::memory_order_acquire) == key)
        {
            delete Hashtable[start];
            Hashtable[start] = nullptr;
            --used_buckets_;
        }
        start = (start + 1) % size;
    }
    used_buckets.store(used_buckets_, std::memory_order_release);
    throw std::invalid_argument("Key not found.");
}

template <typename Key, typename Value>
void ConcurrentHashmap<Key, Value>::visitAll(std::function<void(Key, Value)> func)
{
    if (used_buckets.load(std::memory_order_relaxed) == 0) return;
    uint32_t visited = 0;
    for (uint32_t t = 0; t < size && visited < used_buckets; t++)
    {
        if (Hashtable[t] != nullptr)
        {
            visited++;
            func(Hashtable[t]->key.load(std::memory_order_acquire),
                 Hashtable[t]->value.load(std::memory_order_acquire));
        }
    }
}

template <typename Key, typename Value>
void ConcurrentHashmap<Key, Value>::resize()
{
    std::unique_lock<std::shared_mutex> lock(resize_mutex);

    uint32_t new_size = size * 2;
    ConcurrentBucket<Key, Value>** new_table = new ConcurrentBucket<Key, Value>*[new_size];
    for (uint32_t i = 0; i < new_size; i++)
    {
        new_table[i] = nullptr;
    }

    for (uint32_t i = 0; i < size; i++)
    {
        if (Hashtable[i] != nullptr)
        {
            const uint32_t val = hashCompute(Hashtable[i]->key.load(std::memory_order_relaxed));
            uint32_t start = val % new_size;
            const uint32_t end = (start > 0) ? ((start - 1) % new_size) : new_size - 1;

            while (start != end)
            {
                if (new_table[start] == nullptr)
                {
                    new_table[start] = Hashtable[i];
                    break;
                }
                start = (start + 1) % new_size;
            }
        }
    }
    delete[] Hashtable;
    Hashtable = new_table;
    size = new_size;
}

template class ConcurrentHashmap<Router*, uint16_t>;
template class ConcurrentHashmap<Router*, ConcurrentHashmap<Router*, uint16_t>*>;
