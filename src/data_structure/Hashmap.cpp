#include "Hashmap.h"

#include <stdexcept>
#include <cstring>

#include "Router.h"

template<typename Key, typename Value, typename Func>
Hashmap<Key, Value, Func>::Hashmap() {
    Hashtable = new Bucket<Key, Value> *[size];
    memset(Hashtable, 0, sizeof(Bucket<Key, Value>*) * size);
}

template<typename Key, typename Value, typename Func>
Hashmap<Key, Value, Func>::~Hashmap() {
    for (uint32_t i = 0; i < size; i++) {
        delete Hashtable[i];
    }
    delete[] Hashtable;
}

template<typename Key, typename Value, typename Func>
bool Hashmap<Key, Value, Func>::set(const Key &key, const Value &value) {
    if (used_buckets + 1 > size * load_factor) resize();
    const uint32_t val = hashCompute(key);
    uint32_t start = val % size;
    const uint32_t end = (start > 0) ? ((start - 1) % size) : size - 1;

    bool has_key = false;
    while (start != end) {
        if (Hashtable[start] == nullptr) break;
        if (Hashtable[start]->key == key) {
            has_key = true;
            break;
        }
        start = (start + 1) % size;
    }
    if (start == end) return false;

    if (has_key) delete Hashtable[start];
    else ++used_buckets;
    Hashtable[start] = new Bucket<Key, Value>(key, value);
    return true;
}

template<typename Key, typename Value, typename Func>
void Hashmap<Key, Value, Func>::resize() {
    uint32_t new_size = size * 2;
    Bucket<Key, Value> **new_table = new Bucket<Key,Value> *;
    memset(new_table, 0, sizeof(Bucket<Key,Value>*) * new_size);

    for (uint32_t i = 0; i < size; i++) {
        if (Hashtable[i] != nullptr) {
            const uint32_t val = hashCompute(Hashtable[i]->key);
            uint32_t start = val % new_size;
            const uint32_t end = (start > 0) ? ((start - 1) % new_size) : new_size - 1;
        }
    }
}


template<typename Key, typename Value, typename Func>
Value &Hashmap<Key, Value, Func>::get(const Key &key) {
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

template<typename Key, typename Value, typename Func>
void Hashmap<Key, Value, Func>::visitAll(std::function<void(Key &, Value &)> func) {
    if (used_buckets == 0) return;
    uint32_t visited = 0;
    for (uint32_t t = 0; t < size && visited < used_buckets; t++) {
        if (Hashtable[t] != nullptr) {
            visited++;
            func(Hashtable[t]->key, Hashtable[t]->value);
        }
    }
}

template class Hashmap<Router, int, RouterHashCompute>;
template class Hashmap<Router, Hashmap<Router, int, RouterHashCompute>, RouterHashCompute>;
