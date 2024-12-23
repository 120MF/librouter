#include "HashCompute.hpp"
#include "Router.h"

template <typename T>
uint32_t HashCompute(const T key)
{
    return std::hash<T>()(key);
}

template <>
uint32_t HashCompute(const Router& key)
{
    return std::hash<std::string>()(key.get_uuid());
}

template <>
uint32_t HashCompute(const Router* key)
{
    return std::hash<std::string>()(key->get_uuid());
}

template uint32_t HashCompute<Router>(Router);
template uint32_t HashCompute<Router*>(Router*);
