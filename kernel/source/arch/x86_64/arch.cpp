#include <arch/arch.hpp>

#include <arch/x86_64/io.hpp>

namespace NOS::Arch {

void hcf()
{
    while (true)
    {
        asm volatile("cli; hlt");
    }
    NOS_UNREACHABLE();
}

void pause()
{
    asm volatile("pause");
}

} // namespace NOS::Arch
