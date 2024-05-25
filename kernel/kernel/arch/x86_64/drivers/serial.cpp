#include <kernel/arch/x86_64/drivers/serial.hpp>

#include <kernel/arch/x86_64/arch.hpp>
#include <kernel/arch/x86_64/io.hpp>
#include <kernel/def.hpp>

namespace nos::x86_64::serial {

constexpr u16_t com1 = 0x3F8;
constexpr u16_t com2 = 0x2F8;
// constexpr u16_t com3 = 0x3E8;
// constexpr u16_t com4 = 0x2E8;

bool init_port(u16_t port)
{
    io::out<u8_t>(port + 1U, 0x00); // Disable all interrupts
    io::out<u8_t>(port + 3U, 0x80); // Enable DLAB (set baud rate divisor)
    io::out<u8_t>(port + 0U, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    io::out<u8_t>(port + 1U, 0x00); //                  (hi byte)
    io::out<u8_t>(port + 3U, 0x03); // 8 bits, no parity, one stop bit
    io::out<u8_t>(port + 2U, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    io::out<u8_t>(port + 4U, 0x0B); // IRQs enabled, RTS/DSR set

    io::out<u8_t>(port + 4U, 0x1E); // Set in loopback mode, test the serial chip
    io::out<u8_t>(port + 0U, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if (io::in<u8_t>(port + 0U) != 0xAE)
    {
        return false;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    io::out<u8_t>(port + 4U, 0x0F);

    return true;
}

void early_init()
{
    init_port(com1);
    init_port(com2);
}

char read()
{
    auto has_received = []() {
        return io::in<u8_t>(com1 + 5) & 1 << 0;
    };

    while (!has_received())
    {
        arch::pause();
    }

    return static_cast<char>(io::in<u8_t>(com1));
}

void write(char c)
{
    auto is_empty = []() -> bool {
        return (io::in<u8_t>(com1 + 5) & 1 << 5);
    };

    while (!is_empty())
    {
        arch::pause();
    }

    io::out(com1, static_cast<u8_t>(c));
}

} // namespace nos::x86_64::serial
