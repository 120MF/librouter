#ifndef HASHCOMPUTE_HPP
#define HASHCOMPUTE_HPP
#include <string>

class Router;

template<typename T>
uint32_t HashCompute(const T key) {
    return std::hash<T>()(key);
}

// move the implementation to Router.cpp, avoiding compile error
template<>
uint32_t HashCompute(Router key);

#endif //HASHCOMPUTE_HPP
