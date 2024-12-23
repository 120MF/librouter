#ifndef HASHCOMPUTE_HPP
#define HASHCOMPUTE_HPP
#include <cstdint>
#include <string>

class Router;

template <typename T>
uint32_t HashCompute(T);

template <>
uint32_t HashCompute(Router key);

template <>
uint32_t HashCompute(Router* key);

template uint32_t HashCompute<Router>(Router);

template uint32_t HashCompute<Router*>(Router*);

#endif //HASHCOMPUTE_HPP
