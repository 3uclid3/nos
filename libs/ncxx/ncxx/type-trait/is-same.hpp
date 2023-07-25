#pragma once

#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

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

} // namespace NOS
