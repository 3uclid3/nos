#pragma once

#include <kernel/arch/x86_64/utility/io-port.hpp>

namespace nos::x86_64 {

class serial_port
{
public:
    constexpr serial_port() = default;
    constexpr serial_port(u16_t port);

    void init();

    bool loopback_test();

    u8_t read();
    void write(u8_t c);

private:
    io_port<u8_t> _base_port{};
};

constexpr serial_port::serial_port(u16_t port)
    : _base_port(port)   
{    
}

} // namespace nos::x86_64
