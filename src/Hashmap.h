#ifndef HASHMAP_H
#define HASHMAP_H
#include <cstdint>
#include <functional>

constexpr uint32_t HASH_SIZE = UINT32_MAX;

template<typename T>
struct HashCompute {
    uint32_t operator()(const T &key) {
        return std::hash<T>()(key) % HASH_SIZE;
    }
};

template<typename Key, typename Value>
struct Bucket {
    Bucket(const Key &key, const Value &value): key(key), value(value) {
    }

    Key key;
    Value value;
};

template<typename Key, typename Value, typename Func = HashCompute<Key> >
class Hashmap {
public:
    Hashmap();

    ~Hashmap();

    bool set(const Key &key, const Value &value);

    Value get(const Key &key);

    Value erase(const Key &key);

    Bucket<Key, Value> *Hashtable[HASH_SIZE];

    uint32_t used_buckets = 0;

    bool delete_flags[HASH_SIZE] = {false};
private:
    uint32_t size = HASH_SIZE;
    Func hashCompute;

};


#endif //HASHMAP_H
