#ifndef CONCURRENTHASHMAP_H
#define CONCURRENTHASHMAP_H
#include <atomic>
#include <functional>
#include <shared_mutex>
#include <utils/MaxValue.hpp>
// #include <utils/HashCompute.hpp>

/// Default HashCompute function
/// @tparam T anytype implemented std::hash<T>
/// @param key "Key" in the pair "Key, Value"
/// @return uint32_t type hash number
template<typename T>
uint32_t ConcurrentHashCompute(const T key) {
    return std::hash<T>()(key);
}

/// The bucket structure of ConcurrentHashmap.
/// @tparam Key type of Key. must be copiable and movable
/// @tparam Value type of Value. must be copiable and movable
template<typename Key, typename Value>
struct ConcurrentBucket {
    ConcurrentBucket(const Key &key, const Value &value) {
        // At the time of construct there should not be any concurrency
        // Use std::memory_order_relaxed is enough
        this->key.store(key, std::memory_order_relaxed);
        this->value.store(value, std::memory_order_relaxed);
    }

    std::atomic<Key> key;
    std::atomic<Value> value;
};

/// Hashmap used in concurrent scene.
/// This data structure can't assure sequence of data manipulating
/// @tparam Key type of Key. must be copiable and movable
/// @tparam Value type of Value. must be copiable and movable
template<typename Key, typename Value>
class ConcurrentHashmap {
public:
    /// Construct function with optional custom HashCompute function
    /// @param hashFunction optional custom HashCompute function
    explicit ConcurrentHashmap(std::function<uint32_t(Key)> hashFunction = ConcurrentHashCompute<Key>);

    ~ConcurrentHashmap();

    /// Set the Value corresponded to the Key.
    /// If a value corresponded already exist, the value will be substituted by the new one.
    /// @param key value of key
    /// @param value value of value
    /// @return success flag
    bool set(Key key, Value value);

    /// Get the Value corresponded to the Key.
    /// throw a std::invalid_argument exception if no corresponded value is found.
    /// @param key reference of key
    /// @return the Value corresponded to the Key
    Value get(const Key &key);

    /// Get the Key that have the same hash in the params.
    /// Must pass a callback function to varify the Key found at place and avoid from hash conflict
    /// @param hash the hash same as the Key's that you want to get
    /// @param equal a callback function. Pass the key found at the place, return whether the Key is the one you want to get.
    /// @return The Key that have the same hash in the params.
    Key getKey(const uint32_t &hash, std::function<bool(Key &)> equal);

    //TODO: Maybe we don't need a equal callback, just varify the key's hash is enough

    /// Erase the Key in the Hashmap
    /// @param key reference of key
    void erase(const Key &key);

    /// Visit ALL the Key in the Hashmap, and execute func on each Key & Value pair.
    /// @param func function to be executed on each Key & Value pair
    void visitAll(std::function<void(Key, Value)> func);


    /// Visit ALL the Key in the Hashmap, execute func on each Key & Value pair.
    /// Stop when the flag become false.
    /// @param func function to be executed on each Key & Value pair
    /// @param flag reference to a boolean. Stop iterating when the flag become false.
    void visitAllWhen(std::function<void(Key, Value)> func, bool &flag);

private:
    ConcurrentBucket<Key, Value> **Hashtable;

    void resize();

    float load_factor = 0.75;
    std::atomic<uint32_t> used_buckets = 0;
    uint32_t size = MaxValue<uint8_t>::value;
    std::function<uint32_t(Key)> hashCompute;

    std::shared_mutex resize_mutex;
};


#endif //CONCURRENTHASHMAP_H
