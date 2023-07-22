#pragma once

#include <concept/same-as.hpp>
#include <container/span.hpp>
#include <container/static-array.hpp>

namespace NOS::Serial {

enum class Port : u16_t
{
    COM1 = 0x3F8,
    COM2 = 0x2F8
};

template<typename T>
concept SupportedPortType = (SameAs<T, Port> || SameAs<T, u16_t>);

template<typename... TPort>
requires(SupportedPortType<TPort> && ...)
void earlyInitialize(TPort... port);
void earlyInitialize(Span<Port> ports);
void initialize();

void write(Port port, char c);
char read(Port port);

template<typename... TPort>
requires(SupportedPortType<TPort> && ...)
void earlyInitialize(TPort... port)
{
    Port ports[] = {Port{port}...};
    earlyInitialize(Span<Port>(ports));
}

} // namespace NOS::Serial
