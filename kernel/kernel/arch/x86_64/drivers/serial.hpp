#pragma once

#include <ncxx/concept/same-as.hpp>
#include <ncxx/container/span.hpp>
#include <ncxx/container/static-array.hpp>
#include <ncxx/utility/initializer-list.hpp>

namespace NOS::X86_64::Serial {

using Port = u16_t;

inline constexpr StaticArray Ports = toStaticArray<Port>(
    {0x3F8,
     0x2F8});

bool initializePorts(InitializerList<Port> ports);
bool initializePort(Port port);

void write(Port port, char c);
char read(Port port);

} // namespace NOS::X86_64::Serial
