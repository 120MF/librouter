#include "Hashmap.h"

#include <stdexcept>

template<typename Key, typename Value, typename Func>
Hashmap<Key, Value, Func>::Hashmap() {
    for (auto &i: Hashtable) {
        i = nullptr;
    }
}

template<typename Key, typename Value, typename Func>
Hashmap<Key, Value, Func>::~Hashmap() {
    for (auto &i: Hashtable) {
        delete i;
    }
}

template<typename Key, typename Value, typename Func>
bool Hashmap<Key, Value, Func>::set(const Key &key, const Value &value) {
    if (used_buckets + 1 > HASH_SIZE) return false;
    const uint32_t val = hashCompute(key);
    uint32_t start = val;
    const uint32_t end = (start > 0) ? ((start - 1) % size) : size - 1;

    while (start != end) {
        if (Hashtable[start] == nullptr) break;
        if (Hashtable[start]->key == key) return false;
        start = (start + 1) % size;
    }
    if (start == end) return false;
    Hashtable[start] = new Bucket<Key, Value>(key, value);
    delete_flags[start] = false;
    ++used_buckets;
    return true;
}

template<typename Key, typename Value, typename Func>
Value Hashmap<Key, Value, Func>::get(const Key &key) {
    if (used_buckets == 0) throw std::invalid_argument("Key not found.");

    const uint32_t val = hashCompute(key);
    uint32_t start = val;
    const uint32_t end = (start > 0) ? ((start - 1) % size) : size - 1;
    while (start != end) {
        if (Hashtable[start] == nullptr && !delete_flags[start]) throw std::invalid_argument("Key not found.");
        if (Hashtable[start] != nullptr && Hashtable[start]->key == key) {
            return Hashtable[start]->value;
        }
        start = (start + 1) % size;
    }
    throw std::invalid_argument("Key not found.");
}

template<typename Key, typename Value, typename Func>
Value Hashmap<Key, Value, Func>::erase(const Key &key) {
    if (used_buckets == 0) throw std::invalid_argument("Key not found.");
    const uint32_t val = hashCompute(key);
    uint32_t start = val;
    const uint32_t end = (start > 0) ? ((start - 1) % size) : size - 1;
    while (start != end) {
        if (Hashtable[start] == nullptr && !delete_flags[start]) throw std::invalid_argument("Key not found.");
        if (Hashtable[start] != nullptr && Hashtable[start]->key == key) {
            Value value = Hashtable[start]->value;
            Hashtable[start] = nullptr;
            --used_buckets;
            delete_flags[start] = true;
            return value;
        }
        start = (start + 1) % size;
    }
    throw std::invalid_argument("Key not found.");
}
