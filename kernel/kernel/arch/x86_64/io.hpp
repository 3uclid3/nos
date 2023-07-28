#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/concept/same-as.hpp>

namespace NOS::X86_64::IO {

using PortType = u16_t;

enum class Port : PortType
{
    Debug = 0x00E9
};

template<typename T>
concept SupportedType = SameAs<T, u8_t> || SameAs<T, u16_t> || SameAs<T, u32_t>;

template<typename T>
requires(SupportedType<T>)
static inline T in(PortType port);

template<typename T>
requires(SupportedType<T>)
static inline T in(Port port);

template<typename T>
requires(SupportedType<T>)
static inline void out(PortType port, T value);

template<typename T>
requires(SupportedType<T>)
static inline void out(Port port, T value);

namespace Details {

template<typename T>
requires(SameAs<T, u8_t>)
static inline u8_t inImpl(PortType port)
{
    T data;
    asm volatile("inb %w1, %b0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

template<typename T>
requires(SameAs<T, u16_t>)
static inline u16_t inImpl(PortType port)
{
    T data;
    asm volatile("inw %w1, %b0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

template<typename T>
requires(SameAs<T, u32_t>)
static inline u32_t inImpl(PortType port)
{
    T data;
    asm volatile("inl %w1, %b0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

static inline void outImpl(PortType port, u8_t val)
{
    asm volatile("outb %b0, %w1" ::"a"(val), "Nd"(port));
}

static inline void outImpl(PortType port, u16_t val)
{
    asm volatile("outw %w0, %w1" ::"a"(val), "Nd"(port));
}

static inline void outImpl(PortType port, u32_t val)
{
    asm volatile("outl %0, %w1" ::"a"(val), "Nd"(port));
}

} // namespace Details

template<typename T>
requires(SupportedType<T>)
static inline T in(PortType port)
{
    return Details::inImpl<T>(port);
}

template<typename T>
requires(SupportedType<T>)
static inline T in(Port port)
{
    return Details::inImpl<T>(static_cast<PortType>(port));
}

template<typename T>
requires(SupportedType<T>)
static inline void out(PortType port, T value)
{
    Details::outImpl(static_cast<PortType>(port), value);
}

template<typename T>
requires(SupportedType<T>)
static inline void out(Port port, T value)
{
    Details::outImpl(static_cast<PortType>(port), value);
}

#ifdef NOS_DEBUG
namespace Debug {

static inline void printc(char c)
{
    out<u8_t>(Port::Debug, static_cast<u8_t>(c));
}

static inline void print(StringView str)
{
    for (char c : str)
    {
        printc(c);
    }
}

static inline void println(StringView str)
{
    print(str);
    printc('\n');
}

} // namespace Debug
#endif

} // namespace NOS::X86_64::IO
