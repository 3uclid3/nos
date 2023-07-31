#include <kernel/arch/x86_64/pic.hpp>

#include <kernel/arch/x86_64/io.hpp>
#include <kernel/utility/log.hpp>
#include <ncxx/utility/scope-exit.hpp>

namespace NOS::X86_64 {

void PIC::initialize()
{
    Log::info("pic: initialization");
    Log::ScopeIndent scopeIndent{1};

    // restore mask on exit
    u8_t md = IO::in<u8_t>(MasterDataPort);
    u8_t sd = IO::in<u8_t>(SlaveDataPort);

    auto restoreOnExit = makeScopeExit([md, sd] {
        IO::out<u8_t>(MasterDataPort, md);
        IO::out<u8_t>(SlaveDataPort, sd);
    });

    Log::info("control word 1");
    IO::out<u8_t>(MasterPort, ICW1::Initialize | ICW1::ICW4);
    IO::wait();
    IO::out<u8_t>(SlavePort, ICW1::Initialize | ICW1::ICW4);
    IO::wait();

    Log::info("control word 2");
    IO::out<u8_t>(MasterDataPort, 0x20);
    IO::wait();
    IO::out<u8_t>(SlaveDataPort, 0x28);
    IO::wait();

    Log::info("control word 3");
    IO::out<u8_t>(MasterDataPort, 0x04);
    IO::wait();
    IO::out<u8_t>(SlaveDataPort, 0x02);
    IO::wait();

    Log::info("control word 4");
    IO::out<u8_t>(MasterDataPort, ICW4::Mode8086);
    IO::wait();
    IO::out<u8_t>(SlaveDataPort, ICW4::Mode8086);
    IO::wait();
}

void PIC::disable()
{
    Log::info("pic: disable");

    IO::out<u8_t>(SlaveDataPort, 0xFF);
    IO::out<u8_t>(MasterDataPort, 0xFF);
}

void PIC::mask(u8_t irq)
{
    Log::info("pic: mask {}", irq);
    const u16_t port = irq < 8 ? MasterDataPort : SlaveDataPort;

    if (irq >= 8)
    {
        irq -= 8;
    }

    const u8_t value = IO::in<u8_t>(port) | static_cast<u8_t>(1 << irq);
    IO::out(port, value);
}

void PIC::unmask(u8_t irq)
{
    Log::info("pic: unmask {}", irq);
    const u16_t port = irq < 8 ? MasterDataPort : SlaveDataPort;

    if (irq >= 8)
    {
        irq -= 8;
    }

    const u8_t value = IO::in<u8_t>(port) & ~static_cast<u8_t>(1 << irq);
    IO::out<u8_t>(port, value);
}

void PIC::eoi(u64_t interrupt)
{
    Log::info("pic: eoi {}", interrupt);
    if (interrupt >= 8)
    {
        IO::out<u8_t>(SlaveDataPort, Command::EOI);
    }

    IO::out<u8_t>(MasterDataPort, Command::EOI);
}

namespace {

u16_t read(u8_t ocw3)
{
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    IO::out<u8_t>(PIC::MasterPort, ocw3);
    IO::out<u8_t>(PIC::SlavePort, ocw3);
    return static_cast<u16_t>((IO::in<u8_t>(PIC::SlavePort) << 8) | IO::in<u8_t>(PIC::MasterPort));
}

} // namespace

u16_t PIC::readIRR()
{
    return read(Command::ReadIRR);
}

u16_t PIC::readISR()
{
    return read(Command::ReadISR);
}

} // namespace NOS::X86_64