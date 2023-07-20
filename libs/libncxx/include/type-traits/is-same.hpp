#pragma once

#include <type-traits/integral-constant.hpp>

namespace nos {
    
template<typename T0, typename T1>
struct IsSame : FalseType
{
};

template<typename T>
struct IsSame<T, T> : TrueType
{
};

template<typename T0, typename T1>
static constexpr bool IsSameV = IsSame<T0, T1>::Value;

} // namespace nos
