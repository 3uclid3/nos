#include <kernel/arch/x86_64/arch.hpp>

namespace nos::x86_64 {

void arch::early_init()
{
    _cpu.early_init();
}

void arch::init()
{
    _cpu.init();
}

void arch::halt(bool ints)
{
    if (ints)
    {
        while (true)
        {
            asm volatile("hlt");
        }
    }
    else
    {
        while (true)
        {
            asm volatile("cli; hlt");
        }
    }
}

void arch::pause()
{
    asm volatile("pause");
}

} // namespace nos::x86_64