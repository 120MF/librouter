#include "Hashmap.h"

#include <stdexcept>
#include <cstring>
#include <memory>
#include <utility>

#include "Router.h"

template<typename Key, typename Value>
Hashmap<Key, Value>::Hashmap(std::function<uint32_t(Key)> hashFunction): hashCompute(hashFunction) {
    Hashtable = new Bucket<Key, Value> *[size];
    for (uint32_t i = 0; i < size; i++) {
        Hashtable[i] = nullptr;
    }
}

template<typename Key, typename Value>
Hashmap<Key, Value>::~Hashmap() {
    for (uint32_t i = 0; i < size; i++) {
        delete Hashtable[i];
    }
    delete[] Hashtable;
}

template<typename Key, typename Value>
bool Hashmap<Key, Value>::set(const Key &key, const Value &value) {
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

template<typename Key, typename Value>
void Hashmap<Key, Value>::resize() {
    uint32_t new_size = size * 2;
    Bucket<Key, Value> **new_table = new Bucket<Key, Value> *[new_size];
    for (uint32_t i = 0; i < new_size; i++) {
        new_table[i] = nullptr;
    }

    for (uint32_t i = 0; i < size; i++) {
        if (Hashtable[i] != nullptr) {
            const uint32_t val = hashCompute(Hashtable[i]->key);
            uint32_t start = val % new_size;
            const uint32_t end = (start > 0) ? ((start - 1) % new_size) : new_size - 1;

            while (start != end) {
                if (new_table[start] == nullptr) {
                    new_table[start] = Hashtable[i];
                    break;
                }
                start = (start + 1) % new_size;
            }
        }
    }

    delete [] Hashtable;
    Hashtable = new_table;
    size = new_size;
}


template<typename Key, typename Value>
Value &Hashmap<Key, Value>::get(const Key &key) {
    if (used_buckets == 0) throw std::invalid_argument("Key not found.");

    const uint32_t val = hashCompute(key);
    uint32_t start = val % size;
    const uint32_t end = (start > 0) ? ((start - 1) % size) : size - 1;
    while (start != end) {
        if (Hashtable[start] != nullptr && Hashtable[start]->key == key) {
            return Hashtable[start]->value;
        }
        start = (start + 1) % size;
    }
    throw std::invalid_argument("Key not found.");
}

template<typename Key, typename Value>
Value Hashmap<Key, Value>::erase(const Key &key) {
    if (used_buckets == 0) throw std::invalid_argument("Key not found.");
    const uint32_t val = hashCompute(key);
    uint32_t start = val % size;
    const uint32_t end = (start > 0) ? ((start - 1) % size) : size - 1;
    while (start != end) {
        if (Hashtable[start] != nullptr && Hashtable[start]->key == key) {
            Value value = Hashtable[start]->value;
            Hashtable[start] = nullptr;
            --used_buckets;
            return value;
        }
        start = (start + 1) % size;
    }
    throw std::invalid_argument("Key not found.");
}

template<typename Key, typename Value>
void Hashmap<Key, Value>::visitAll(std::function<void(Key &, Value &)> func) {
    if (used_buckets == 0) return;
    uint32_t visited = 0;
    for (uint32_t t = 0; t < size && visited < used_buckets; t++) {
        if (Hashtable[t] != nullptr) {
            visited++;
            func(Hashtable[t]->key, Hashtable[t]->value);
        }
    }
}

template class Hashmap<Router *, uint16_t>;
template class Hashmap<Router *, Hashmap<Router *, uint16_t> *>;
