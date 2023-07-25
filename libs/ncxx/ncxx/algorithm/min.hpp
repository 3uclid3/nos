#pragma once

namespace NOS {

// TODO Compare functor

template<typename T>
constexpr T min(T lhs, T rhs);

template<typename T, typename... Args>
constexpr T min(T lhs, T rhs, Args... args);

template<typename T>
constexpr T min(T lhs, T rhs)
{
    return lhs > rhs ? rhs : lhs;
}

template<typename T, typename... Args>
constexpr T min(T lhs, T rhs, Args... args)
{
    return min(min(lhs, rhs), args...);
}

} // namespace NOS
