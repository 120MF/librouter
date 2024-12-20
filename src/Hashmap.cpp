#include "Hashmap.h"

#include <stdexcept>
#include "Router.h"

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
    else {
        delete_flags[start] = false;
        ++used_buckets;
    }
    Hashtable[start] = new Bucket<Key, Value>(key, value);
    return true;
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
