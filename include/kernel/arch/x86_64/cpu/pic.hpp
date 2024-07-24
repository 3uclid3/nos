#pragma once

#include <arch/x86_64/io_port.hpp>
#include <kdef.hpp>

namespace nos::x86_64 {

class pic
{
public:
    void init();
    void disable();

    void mask_irq(std::uint8_t irq);
    void unmask_irq(std::uint8_t irq);

    void eoi(std::uint64_t interrupt);

private:
    static constexpr std::uint8_t command_offset{0};
    static constexpr std::uint8_t data_offset{1};

    io_port<std::uint8_t> _master{0x20};
    io_port<std::uint8_t> _slave{0xA0};
};

} // namespace nos::x86_64
