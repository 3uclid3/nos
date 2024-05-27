#include <kernel/arch/x86_64/cpu/cpu.hpp>

namespace nos::x86_64 {

void cpu::early_init()
{
    // TODO Support multi-core
    _gdt.load(0);
}

void cpu::init()
{
}

} // namespace nos::x86_64
