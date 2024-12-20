#ifndef HASHMAP_H
#define HASHMAP_H
#include <cstdint>
#include <functional>

constexpr uint32_t MAX_HASH_SIZE = UINT16_MAX+1;
constexpr uint32_t INIT_HASH_SIZE = UINT8_MAX+1;

template<typename T>
struct HashCompute {
    uint32_t operator()(const T &key) const {
        return std::hash<T>()(key);
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

    Value &get(const Key &key);

    Value erase(const Key &key);

    void visitAll(std::function<void(Key &, Value &)> func);

private:
    Bucket<Key, Value> **Hashtable;
    void resize();
    float load_factor = 0.75;
    uint32_t used_buckets = 0;
    uint32_t size = INIT_HASH_SIZE;
    Func hashCompute;
};


#endif //HASHMAP_H
