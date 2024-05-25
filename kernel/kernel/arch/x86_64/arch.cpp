#include <kernel/arch/x86_64/arch.hpp>

#include <kernel/def.hpp>

namespace nos::x86_64::arch {

void init()
{
}

void halt(bool ints)
{
    if (ints == true)
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

void pause()
{
    asm volatile("pause");
}

void shutdown(bool now)
{
    NOS_UNUSED(now);
}

void reboot(bool now)
{
    NOS_UNUSED(now);
}

} // namespace nos::x86_64::arch