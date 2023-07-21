#pragma once

#include <type-traits/integral-constant.hpp>

namespace N {
    
template<typename T>
struct IsConst : FalseType
{
};

template<typename T>
struct IsConst<const T> : TrueType
{
};

template<typename T>
static constexpr bool IsConstV = IsConst<T>::Value;

} // namespace N
