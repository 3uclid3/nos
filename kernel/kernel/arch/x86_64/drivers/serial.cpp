#include <kernel/arch/x86_64/drivers/serial.hpp>

#include <kernel/arch/x86_64/cpu.hpp>
#include <kernel/arch/x86_64/io.hpp>

namespace NOS::X86_64::Serial {

bool initializePorts(InitializerList<Port> ports)
{
    bool valid = true;
    for (Port port : ports)
    {
        if (initializePort(port))
        {
            valid = false;
        }
    }
    return valid;
}

bool initializePort(u16_t port)
{
    IO::out<u8_t>(port + 1U, 0x00); // Disable all interrupts
    IO::out<u8_t>(port + 3U, 0x80); // Enable DLAB (set baud rate divisor)
    IO::out<u8_t>(port + 0U, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    IO::out<u8_t>(port + 1U, 0x00); //                  (hi byte)
    IO::out<u8_t>(port + 3U, 0x03); // 8 bits, no parity, one stop bit
    IO::out<u8_t>(port + 2U, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    IO::out<u8_t>(port + 4U, 0x0B); // IRQs enabled, RTS/DSR set

    IO::out<u8_t>(port + 4U, 0x1E); // Set in loopback mode, test the serial chip
    IO::out<u8_t>(port + 0U, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if (IO::in<u8_t>(port + 0U) != 0xAE)
    {
        return false;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    IO::out<u8_t>(port + 4U, 0x0F);

    return true;
}

void write(u16_t port, char c)
{
    auto isEmpty = [port]() -> bool {
        return (IO::in<u8_t>(port + 5) & 1 << 5);
    };

    while (!isEmpty())
    {
        CPU::pause();
    }

    IO::out(port, static_cast<u8_t>(c));
}

char read(u16_t port)
{
    auto hasReceived = [port]() {
        return IO::in<u8_t>(port + 5) & 1 << 0;
    };

    while (!hasReceived())
    {
        CPU::pause();
    }

    return static_cast<char>(IO::in<u8_t>(port));
}

} // namespace NOS::X86_64::Serial
