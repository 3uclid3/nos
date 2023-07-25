#pragma once

#include <ncxx/base-types.hpp>

namespace NOS {

constexpr bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

constexpr u8_t toDigit(char c)
{
    return static_cast<u8_t>(c - '0');
}

} // namespace NOS
