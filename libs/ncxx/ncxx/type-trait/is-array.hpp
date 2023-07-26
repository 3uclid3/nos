#pragma once

#include <ncxx/container/array.hpp>
#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsArray : FalseType
{};

template<typename T>
struct IsArray<Array<T>> : TrueType
{};

template<typename T>
constexpr bool IsArrayV = IsArray<T>::Value;

} // namespace NOS
