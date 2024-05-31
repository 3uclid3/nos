#include <kernel/arch/x86_64/cpu/cpu.hpp>

namespace nos::x86_64 {

void cpu::early_init()
{
    _gdt.load(0);

    _idt.init();
}

void cpu::init()
{
}

void cpu::pause()
{
    asm volatile("pause");
}

} // namespace nos::x86_64
