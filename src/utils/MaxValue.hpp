#ifndef MAXVALUE_HPP
#define MAXVALUE_HPP
#include <cstdint>

template<typename T>
struct MaxValue;

template<>
struct MaxValue<uint8_t> {
    static constexpr uint8_t value = UINT8_MAX;
};

template<>
struct MaxValue<uint16_t> {
    static constexpr uint16_t value = UINT16_MAX;
};

template<>
struct MaxValue<uint32_t> {
    static constexpr int value = UINT32_MAX;
};

template<>
struct MaxValue<unsigned long> {
    static constexpr int value = UINT32_MAX;
};

template<>
struct MaxValue<int> {
    static constexpr int value = INT32_MAX;
};


#endif //MAXVALUE_HPP
