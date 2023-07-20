#pragma once

#include <base-types.hpp>
#include <concept/same_as.hpp>

namespace nos::arch::x86_64::io {

namespace details {

template<typename T>
requires(same_as<T, u8_t>)
static inline u8_t in(u16_t port)
{
    T data;
    asm volatile("inb %w1, %b0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

template<typename T>
requires(same_as<T, u16_t>)
static inline u16_t in(u16_t port)
{
    T data;
    asm volatile("inw %w1, %b0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

template<typename T>
requires(same_as<T, u32_t>)
static inline u32_t in(u16_t port)
{
    T data;
    asm volatile("inl %w1, %b0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

static inline void out(u16_t port, u8_t val)
{
    asm volatile("outb %b0, %w1" ::"a"(val), "Nd"(port));
}

static inline void out(u16_t port, u16_t val)
{
    asm volatile("outw %w0, %w1" ::"a"(val), "Nd"(port));
}

static inline void out(u16_t port, u32_t val)
{
    asm volatile("outl %0, %w1" ::"a"(val), "Nd"(port));
}

} // namespace details

template<typename T>
concept io_type = same_as<T, u8_t> || same_as<T, u16_t> || same_as<T, u32_t>;

enum class port : u16_t
{
    debug = 0x00E9
};

template<typename T>
requires(io_type<T>)
static inline u8_t in(port port)
{
    return details::in<T>(static_cast<u16_t>(port));
}

template<typename T>
requires(io_type<T>)
static inline u8_t in(u16_t port)
{
    return details::in<T>(port);
}

template<typename T>
requires(io_type<T>)
static inline void out(port port, T value)
{
    details::out(static_cast<u16_t>(port), value);
}

template<typename T>
requires(io_type<T>)
static inline void out(u16_t port, T value)
{
    details::out(port, value);
}

} // namespace nos::arch::x86_64::io
