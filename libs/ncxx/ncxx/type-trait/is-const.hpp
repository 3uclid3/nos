#pragma once

#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsConst : FalseType
{
};

template<typename T>
struct IsConst<const T> : TrueType
{
};

template<typename T>
inline constexpr bool IsConstV = IsConst<T>::Value;

} // namespace NOS
