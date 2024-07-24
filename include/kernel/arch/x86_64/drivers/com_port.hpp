#pragma once

#include <cstdint>

#include <arch/x86_64/drivers/serial_port.hpp>
#include <kdef.hpp>

namespace nos::x86_64 {

enum class standard_com_port : std::uint16_t
{
    com1 = 0x3F8,
    com2 = 0x2F8,
    com3 = 0x3E8,
    com4 = 0x2E8,
};

class com_port : private serial_port
{
public:
    constexpr com_port() = default;
    constexpr com_port(std::uint16_t port);
    constexpr com_port(standard_com_port port);

    using serial_port::init;
    using serial_port::loopback_test;

    char read();
    void write(char c);
};

constexpr com_port::com_port(std::uint16_t port)
    : serial_port(port)
{
}

constexpr com_port::com_port(standard_com_port port)
    : com_port(static_cast<std::uint16_t>(port))
{
}

} // namespace nos::x86_64
