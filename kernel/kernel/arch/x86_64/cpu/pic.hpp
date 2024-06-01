#pragma once

#include <kernel/arch/x86_64/utility/io_port.hpp>
#include <kernel/def.hpp>

namespace nos::x86_64 {

class pic
{
public:
    void init();
    void disable();

    void mask_irq(u8_t irq);
    void unmask_irq(u8_t irq);

    void eoi(u64_t interrupt);

private:
    static constexpr u8_t command_offset{0};
    static constexpr u8_t data_offset{1};

    io_port<u8_t> _master{0x20};
    io_port<u8_t> _slave{0xA0};
};

} // namespace nos::x86_64
