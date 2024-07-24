#include <arch/x86_64/drivers/serial_port.hpp>

#include <arch/x86_64/cpu.hpp>

namespace nos::x86_64 {

void serial_port::init()
{
    // Disable all interrupts
    _io_port.write(0x00, 1);

    // Enable DLAB (set baud rate divisor)
    _io_port.write(0x80, 3);
    _io_port.write(0x03, 0); // Set divisor to 3 (lo byte) 38400 baud
    _io_port.write(0x00, 1); // (hi byte)

    // Configure line control (8 bits, no parity, one stop bit)
    _io_port.write(0x03, 3);

    // Enable FIFO, clear them, with 14-byte threshold
    _io_port.write(0xC7, 2);

    // Enable IRQs, RTS/DSR set
    _io_port.write(0x0B, 4);

    // Enable all interrupts
    // _io_port.write(0x01, 1);
}

bool serial_port::loopback_test()
{
    // Set in loopback mode, test the serial chip
    _io_port.write(0x1E, 4);

    // Test serial chip (send byte 0xAE and check if serial returns same byte)
    _io_port.write(0xAE, 0);

    // Check if serial is faulty (i.e: not same byte as sent)
    if (_io_port.read(0) != 0xAE)
    {
        return false;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    _io_port.write(0x0F, 4);

    return true;
}

std::uint8_t serial_port::read()
{
    auto has_received = [this]() {
        return _io_port.read(5) & 1 << 0;
    };

    while (!has_received())
    {
        cpu::pause();
    }

    return static_cast<std::uint8_t>(_io_port.read());
}

void serial_port::write(std::uint8_t c)
{
    auto is_empty = [this]() -> bool {
        return _io_port.read(5) & 1 << 5;
    };

    while (!is_empty())
    {
        cpu::pause();
    }

    _io_port.write(c);
}

} // namespace nos::x86_64
