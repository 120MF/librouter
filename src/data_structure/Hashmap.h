#ifndef HASHMAP_H
#define HASHMAP_H
#include <cstdint>
#include <functional>
#include "utils/HashCompute.hpp"
#include "utils/MaxValue.hpp"

template<typename Key, typename Value>
struct Bucket {
    Bucket(const Key &key, const Value &value): key(key), value(value) {
    }

    Key key;
    Value value;
};

template<typename Key, typename Value>
class Hashmap {
public:
    explicit Hashmap(std::function<uint32_t(Key)> hashFunction = HashCompute<Key>);

    ~Hashmap();

    bool set(Key key, Value value);

    Value &get(const Key &key);

    void erase(const Key &key);

    void visitAll(std::function<void(Key &, Value &)> func);

private:
    Bucket<Key, Value> **Hashtable;

    void resize();

    float load_factor = 0.75;
    uint32_t used_buckets = 0;
    uint32_t size = MaxValue<uint8_t>::value;
    std::function<uint32_t(Key)> hashCompute;
};


#endif //HASHMAP_H
