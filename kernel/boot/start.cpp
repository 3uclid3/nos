#include <arch/arch.hpp>
#include <boot/loader.hpp>
#include <kernel.hpp>

extern "C" void _start(void)
{
    if (!nos::boot::loader::is_ready())
    {
        nos::arch::hcf();
    }

    nos::kernel kernel;

    kernel.init();
    kernel.run();

    nos::arch::hcf();
}
