#pragma once

#include <def.hpp>
#include <stddef.h>
#include <stdint.h>

namespace NOS {

using nullptr_t = decltype(nullptr);

using intptr_t = ::intptr_t;
using uintptr_t = ::uintptr_t;

using s8_t = ::int8_t;
using s16_t = ::int16_t;
using s32_t = ::int32_t;
using s64_t = ::int64_t;

using u8_t = ::uint8_t;
using u16_t = ::uint16_t;
using u32_t = ::uint32_t;
using u64_t = ::uint64_t;

using f32_t = float;
using f64_t = double;
using f128_t = long double;

using size_t = ::size_t;

enum class byte : u8_t
{
    zero = 0x00
};

enum class alignment_t : size_t
{
};

constexpr bool isDigit(char c);
constexpr u8_t toDigit(char c);

constexpr bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

constexpr u8_t toDigit(char c)
{
    return static_cast<u8_t>(c - '0');
}

} // namespace NOS
