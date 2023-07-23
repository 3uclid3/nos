#pragma once

#include <base-types.hpp>
#include <type-traits/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsIntegral : FalseType
{};

// clang-format off
template<> struct IsIntegral<bool> : TrueType {};
template<> struct IsIntegral<char> : TrueType {};
template<> struct IsIntegral<u8_t> : TrueType {};
template<> struct IsIntegral<s8_t> : TrueType {};
template<> struct IsIntegral<u16_t> : TrueType {};
template<> struct IsIntegral<s16_t> : TrueType {};
template<> struct IsIntegral<u32_t> : TrueType {};
template<> struct IsIntegral<s32_t> : TrueType {};
template<> struct IsIntegral<u64_t> : TrueType {};
template<> struct IsIntegral<s64_t> : TrueType {};
// clang-format on

template<typename T>
inline constexpr bool IsIntegralV = IsIntegral<T>::Value;

} // namespace NOS
