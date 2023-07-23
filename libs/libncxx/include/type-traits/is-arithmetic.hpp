#pragma once

#include <type-traits/integral-constant.hpp>
#include <type-traits/is-floating-point.hpp>
#include <type-traits/is-integral.hpp>

namespace NOS {

template<typename T>
struct IsArithmetic : BoolConstant<IsIntegralV<T> || IsFloatingPointV<T>>
{};

template<typename T>
inline constexpr bool IsArithmeticV = IsArithmetic<T>::Value;

} // namespace NOS
