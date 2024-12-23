#ifndef CONCURRENTHASHMAP_H
#define CONCURRENTHASHMAP_H
#include <atomic>
#include <functional>
#include <shared_mutex>
#include <utils/MaxValue.hpp>
// #include <utils/HashCompute.hpp>

template<typename T>
uint32_t ConcurrentHashCompute(const T key) {
    return std::hash<T>()(key);
}

template <typename Key, typename Value>
struct ConcurrentBucket
{
    ConcurrentBucket(const Key& key, const Value& value)
    {
        this->key.store(key, std::memory_order_relaxed);
        this->value.store(value, std::memory_order_relaxed);
    }

    std::atomic<Key> key;
    std::atomic<Value> value;
};

template <typename Key, typename Value>
class ConcurrentHashmap
{
public:
    explicit ConcurrentHashmap(std::function<uint32_t(Key)> hashFunction = ConcurrentHashCompute<Key>);

    ~ConcurrentHashmap();

    bool set(Key key, Value value);

    Value get(const Key& key);

    void erase(const Key& key);

    void visitAll(std::function<void(Key, Value)> func);

private:
    ConcurrentBucket<Key, Value>** Hashtable;
    void resize();

    float load_factor = 0.75;
    std::atomic<uint32_t> used_buckets = 0;
    uint32_t size = MaxValue<uint8_t>::value;
    std::function<uint32_t(Key)> hashCompute;

    std::shared_mutex resize_mutex;
};


#endif //CONCURRENTHASHMAP_H
