#include <drivers/serial.hpp>

#include <arch/arch.hpp>
#include <arch/x86_64/io.hpp>
#include <config.hpp>
#include <debug/assert.hpp>

namespace NOS::Serial {

void print(StringView str)
{
    for(char c : str)
    {
        Arch::IO::out(Arch::IO::Port::Debug, static_cast<u8_t>(c));
    }
}

void println(StringView str)
{
    print(str);
        
    Arch::IO::out(Arch::IO::Port::Debug, static_cast<u8_t>('\n'));
}

void earlyInitialize(Span<Port> ports)
{
    auto initializePort = [](Port port) {
        u16_t p = static_cast<u16_t>(port);

        Arch::IO::out<u8_t>(p + 1U, 0x00); // Disable all interrupts
        Arch::IO::out<u8_t>(p + 3U, 0x80); // Enable DLAB (set baud rate divisor)
        Arch::IO::out<u8_t>(p + 0U, 0x03); // Set divisor to 3 (lo byte) 38400 baud
        Arch::IO::out<u8_t>(p + 1U, 0x00); //                  (hi byte)
        Arch::IO::out<u8_t>(p + 3U, 0x03); // 8 bits, no parity, one stop bit
        Arch::IO::out<u8_t>(p + 2U, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
        Arch::IO::out<u8_t>(p + 4U, 0x0B); // IRQs enabled, RTS/DSR set

#if NOS_ENABLE_SERIAL_PORT_TESTING
        Arch::IO::out<u8_t>(p + 4U, 0x1E); // Set in loopback mode, test the serial chip
        Arch::IO::out<u8_t>(p + 0U, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

        // Check if serial is faulty (i.e: not same byte as sent)
        if (Arch::IO::in<u8_t>(p + 0U) != 0xAE)
        {
            Arch::IO::Debug::println("Serial: Port is faulty");
            return;
        }

        // If serial is not faulty set it in normal operation mode
        // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
        Arch::IO::out<u8_t>(p + 4U, 0x0F);
#endif
    };

    for (Port port : ports)
    {
        initializePort(port);
    }
}

void initialize()
{
}

void write(Port port, char c)
{
    uint16_t rawPort = static_cast<u16_t>(port);

    auto isEmpty = [](u16_t p) -> bool {
        return (Arch::IO::in<u8_t>(p + 5) & 1 << 5);
    };

    while (!isEmpty(rawPort))
    {
        Arch::pause();
    }

    Arch::IO::out(rawPort, static_cast<uint8_t>(c));
}

char read(Port port)
{
    uint16_t rawPort = static_cast<u16_t>(port);

    auto hasReceived = [](u16_t p) {
        return Arch::IO::in<u8_t>(p + 5) & 1 << 0;
    };

    while (!hasReceived(rawPort))
    {
        Arch::pause();
    }

    return static_cast<char>(Arch::IO::in<u8_t>(rawPort));
}

} // namespace NOS::Serial
