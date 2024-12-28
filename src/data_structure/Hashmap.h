#ifndef HASHMAP_H
#define HASHMAP_H
#include <cstdint>
#include <functional>
#include "utils/MaxValue.hpp"
// #include "utils/HashCompute.hpp"

/// Default HashCompute function
/// @tparam T anytype implemented std::hash<T>
/// @param key "Key" in the pair "Key, Value"
/// @return uint32_t type hash number
template<typename T>
uint32_t HashCompute(const T key) {
    return std::hash<T>()(key);
}

/// The bucket structure of Hashmap.
/// @tparam Key type of Key.
/// @tparam Value type of Value.
template<typename Key, typename Value>
struct Bucket {
    Bucket(const Key &key, const Value &value): key(key), value(value) {
    }

    Key key;
    Value value;
};

/// Hashmap data structure. Storing Key & Value pair.
/// @tparam Key type of Key.
/// @tparam Value type of Value.
template<typename Key, typename Value>
class Hashmap {
public:
    /// Construct function with optional custom HashCompute function
    /// @param hashFunction optional custom HashCompute function
    explicit Hashmap(std::function<uint32_t(Key)> hashFunction = HashCompute<Key>);

    ~Hashmap();

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
    Value &get(const Key &key);

    /// Erase the Key in the Hashmap
    /// @param key reference of key
    void erase(const Key &key);

    /// Visit ALL the Key in the Hashmap, and execute func on each Key & Value pair.
    /// @param func function to be executed on each Key & Value pair
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
