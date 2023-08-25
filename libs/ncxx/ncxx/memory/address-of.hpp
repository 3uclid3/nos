#pragma once

namespace NOS {

template<typename T>
constexpr T* addressOf(T& x)
{
    return __builtin_addressof(x);
}

template<typename T>
constexpr T* addressOf(const T&&) = delete;

} // namespace NOS
