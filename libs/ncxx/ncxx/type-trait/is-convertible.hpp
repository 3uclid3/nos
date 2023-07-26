#pragma once

#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename TFrom, typename TTo>
struct IsConvertible : BoolConstant<__is_convertible(TFrom, TTo)>
{};

template<typename TFrom, typename TTo>
inline constexpr bool IsConvertibleV = IsConvertible<TFrom, TTo>::Value;

} // namespace NOS
