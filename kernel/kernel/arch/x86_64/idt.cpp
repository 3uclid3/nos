#include <kernel/arch/x86_64/idt.hpp>

#include <kernel/arch/x86_64/gdt.hpp>
#include <kernel/arch/x86_64/interrupt.hpp>

extern "C" void* NOS_interruptTable[];

namespace NOS::X86_64 {

void IDT::Entry::set(void* isr_, uint8_t typeAttr_, uint8_t ist_)
{
    u64_t isr = reinterpret_cast<u64_t>(isr_);
    offset1 = static_cast<u16_t>(isr);
    selector = GDT::Selector::Code;
    ist = ist_;
    typeAttr = typeAttr_;
    offset2 = static_cast<u16_t>(isr >> 16);
    offset3 = static_cast<u32_t>(isr >> 32);
    zero = 0;
}

void IDT::load()
{
    Log::info("idt: loading");

    for (size_t i = 0; i < _entries.size(); ++i)
    {
        _entries[i].set(NOS_interruptTable[i]);
    }

    Register r = makeRegister();

    Interrupt::disable();
    asm volatile("lidt %0" ::"memory"(r));
    Interrupt::enable();
}

IDT::Register IDT::makeRegister() const
{
    return {.limit = static_cast<u16_t>(sizeof(Entry) * _entries.size() - 1),
            .base = reinterpret_cast<uintptr_t>(_entries.data())};
}

} // namespace NOS::X86_64
