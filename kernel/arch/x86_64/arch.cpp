#include <arch/arch.hpp>

namespace nos::arch {

void hcf()
{
    while (true)
    {
        asm volatile("cli; hlt");
    }    
}

} // namespace nos::arch
