#pragma once

#include <ncxx/basic-types.hpp>

namespace NOS::Details {

template<typename T>
requires(SameAs<T, u8_t>)
static inline u8_t inImpl(u16_t port)
{
    T data;
    asm volatile("inb %w1, %b0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

template<typename T>
requires(SameAs<T, u16_t>)
static inline u16_t inImpl(u16_t port)
{
    T data;
    asm volatile("inw %w1, %b0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

template<typename T>
requires(SameAs<T, u32_t>)
static inline u32_t inImpl(u16_t port)
{
    T data;
    asm volatile("inl %w1, %b0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

static inline void outImpl(u16_t port, u8_t val)
{
    asm volatile("outb %b0, %w1" ::"a"(val), "Nd"(port));
}

static inline void outImpl(u16_t port, u16_t val)
{
    asm volatile("outw %w0, %w1" ::"a"(val), "Nd"(port));
}

static inline void outImpl(u16_t port, u32_t val)
{
    asm volatile("outl %0, %w1" ::"a"(val), "Nd"(port));
}

} // namespace NOS::Details
