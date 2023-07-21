#pragma once

#include <base-types.hpp>
#include <concept/same-as.hpp>

namespace nos::arch::x86_64::io {

enum class Port : u16_t
{
    Debug = 0x00E9
};

template<typename T>
concept SupportedType = SameAs<T, u8_t> || SameAs<T, u16_t> || SameAs<T, u32_t>;

template<typename T>
requires(SameAs<T, u8_t>)
static inline u8_t in(u16_t port)
{
    T data;
    asm volatile("inb %w1, %b0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

template<typename T>
requires(SameAs<T, u16_t>)
static inline u16_t in(u16_t port)
{
    T data;
    asm volatile("inw %w1, %b0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

template<typename T>
requires(SameAs<T, u32_t>)
static inline u32_t in(u16_t port)
{
    T data;
    asm volatile("inl %w1, %b0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

template<typename T>
requires(SupportedType<T>)
static inline T in(Port port)
{
    return in<T>(static_cast<u16_t>(port));
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

template<typename T>
requires(SupportedType<T>)
static inline void out(Port port, T value)
{
    out(static_cast<u16_t>(port), value);
}

} // namespace nos::arch::x86_64::io
