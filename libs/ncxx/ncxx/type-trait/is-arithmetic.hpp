#pragma once

#include <ncxx/type-trait/integral-constant.hpp>
#include <ncxx/type-trait/is-floating-point.hpp>
#include <ncxx/type-trait/is-integral.hpp>

namespace NOS {

template<typename T>
struct IsArithmetic : BoolConstant<IsIntegralV<T> || IsFloatingPointV<T>>
{};

template<typename T>
inline constexpr bool IsArithmeticV = IsArithmetic<T>::Value;

} // namespace NOS
