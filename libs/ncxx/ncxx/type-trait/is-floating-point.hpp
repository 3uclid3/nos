#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsFloatingPoint : FalseType
{};

// clang-format off
template<> struct IsFloatingPoint<f32_t> : TrueType {};
template<> struct IsFloatingPoint<f64_t> : TrueType {};
template<> struct IsFloatingPoint<f128_t> : TrueType {};
// clang-format on

template<typename T>
inline constexpr bool IsFloatingPointV = IsFloatingPoint<T>::Value;

} // namespace NOS
