#pragma once

#include <kernel/arch/x86_64/details/io-impl.hpp>
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
    return in<T>(static_cast<PortType>(port));
}

template<typename T>
requires(SupportedType<T>)
static inline void out(PortType port, T value)
{
    Details::outImpl(port, value);
}

template<typename T>
requires(SupportedType<T>)
static inline void out(Port port, T value)
{
    out(static_cast<PortType>(port), value);
}

} // namespace NOS::X86_64::IO
