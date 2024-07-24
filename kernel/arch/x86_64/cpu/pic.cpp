#include <arch/x86_64/cpu/pic.hpp>

#include <klog.hpp>

namespace nos::x86_64 {

void pic::init()
{
    log::info("nos: pic init");

    // restore mask on exit
    const std::uint8_t md = _master.read(data_offset);
    const std::uint8_t sd = _slave.read(data_offset);

    _master.write(0x11, command_offset);
    _slave.write(0x11, command_offset);

    _master.write(0x20, data_offset);
    _slave.write(0x28, data_offset);

    _master.write(0x04, data_offset);
    _slave.write(0x02, data_offset);

    _master.write(0x01, data_offset);
    _slave.write(0x01, data_offset);

    // restore mask
    _master.write(md, data_offset);
    _slave.write(sd, data_offset);
}

void pic::disable()
{
    _master.write(0xFF, data_offset);
    _slave.write(0xFF, data_offset);
}

void pic::mask_irq(std::uint8_t irq)
{
    auto& port = irq < 8 ? _master : _slave;

    if (irq >= 8)
    {
        irq -= 8;
    }

    const std::uint8_t value = port.read(data_offset) | static_cast<std::uint8_t>(1 << irq);
    port.write(value, data_offset);
}

void pic::unmask_irq(std::uint8_t irq)
{
    auto& port = irq < 8 ? _master : _slave;

    if (irq >= 8)
    {
        irq -= 8;
    }

    const std::uint8_t value = port.read(data_offset) & ~static_cast<std::uint8_t>(1 << irq);
    port.write(value, data_offset);
}

void pic::eoi(std::uint64_t interrupt)
{
    if (interrupt >= 8)
    {
        _slave.write(0x20, data_offset);
    }

    _master.write(0x20, data_offset);
}

} // namespace nos::x86_64