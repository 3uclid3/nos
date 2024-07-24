#pragma once

#include <cstdint>

#include <arch/x86_64/io_port.hpp>

namespace nos::x86_64 {

class serial_port
{
public:
    constexpr serial_port() = default;
    constexpr serial_port(std::uint16_t port);

    void init();

    bool loopback_test();

    std::uint8_t read();
    void write(std::uint8_t c);

private:
    io_port<std::uint8_t> _io_port{};
};

constexpr serial_port::serial_port(std::uint16_t port)
    : _io_port(port)
{
}

} // namespace nos::x86_64
