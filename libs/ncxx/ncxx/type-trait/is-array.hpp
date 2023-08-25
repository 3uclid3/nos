#pragma once

#include <ncxx/container/array.hpp>
#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsArray : FalseType
{};

template<typename T, typename TAllocator, typename TSize>
struct IsArray<Array<T, TAllocator, TSize>> : TrueType
{};

template<typename T>
constexpr bool IsArrayV = IsArray<T>::Value;

} // namespace NOS
