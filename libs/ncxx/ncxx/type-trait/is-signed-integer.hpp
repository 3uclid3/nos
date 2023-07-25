#pragma once

#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

// clang-format off
template <typename T> struct IsSignedInteger : public FalseType {};
template <> struct IsSignedInteger<signed char> : public TrueType {};
template <> struct IsSignedInteger<signed short> : public TrueType {};
template <> struct IsSignedInteger<signed int> : public TrueType {};
template <> struct IsSignedInteger<signed long> : public TrueType {};
template <> struct IsSignedInteger<signed long long> : public TrueType {};
// clang-format on

template<typename T>
inline constexpr bool IsSignedIntegerV = IsSignedInteger<T>::Value;

} // namespace NOS
