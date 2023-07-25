#include <kernel/arch/arch.hpp>

#include <kernel/arch/x86_64/io.hpp>

namespace NOS::Arch {

void hcf()
{
    while (true)
    {
        asm volatile("cli; hlt");
    }
    NOS_UNREACHABLE();
}

void halt()
{
    while (true)
    {
        asm volatile("hlt");
    }
    NOS_UNREACHABLE();
}

void pause()
{
    asm volatile("pause");
}

} // namespace NOS::Arch
