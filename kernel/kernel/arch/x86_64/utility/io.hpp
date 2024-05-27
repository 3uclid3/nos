#pragma once

#include "../../../../../subprojects/nxx/nxx/nxx/concept/same-as.hpp"
#include "../../../def.hpp"

namespace nos::x86_64::io {

template<typename T>
concept is_supported_type = nxx::same_as<T, u8_t> || nxx::same_as<T, u16_t> || nxx::same_as<T, u32_t>;

template<typename T>
requires(is_supported_type<T>)
static inline T in(u16_t port)
{
    T data{};
    if constexpr (nxx::is_same<T, u8_t>)
    {
        asm volatile("inb %w1, %b0" : "=a"(data) : "Nd"(port));
    }
    else if constexpr (nxx::is_same<T, u16_t>)
    {
        asm volatile("inw %w1, %w0" : "=a"(data) : "Nd"(port));
    }
    else if constexpr (nxx::is_same<T, u32_t>)
    {
        asm volatile("inl %w1, %0" : "=a"(data) : "Nd"(port));
    }
    return data;
}

template<typename T>
requires(is_supported_type<T>)
static inline void out(u16_t port, T data)
{
    if constexpr (nxx::is_same<T, u8_t>)
    {
        asm volatile("outb %b0, %w1" ::"a"(data), "Nd"(port));
    }
    else if constexpr (nxx::is_same<T, u16_t>)
    {
        asm volatile("outw %w0, %w1" ::"a"(data), "Nd"(port));
    }
    else if constexpr (nxx::is_same<T, u32_t>)
    {
        asm volatile("outl %0, %w1" ::"a"(data), "Nd"(port));
    }
}

} // namespace nos::x86_64::io
