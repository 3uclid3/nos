#pragma once

#include <ncxx/container/static-array.hpp>
#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsStaticArray : FalseType
{};

template<typename T, size_t TSize>
struct IsStaticArray<StaticArray<T, TSize>> : TrueType
{};

template<typename T>
constexpr bool IsStaticArrayV = IsStaticArray<T>::Value;

} // namespace NOS
