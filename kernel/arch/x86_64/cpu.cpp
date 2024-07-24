#include <arch/x86_64/cpu.hpp>

namespace nos::x86_64 {

void cpu::early_init()
{
}

void cpu::init()
{
}

void cpu::pause()
{
    asm volatile("pause");
}

} // namespace nos::x86_64