#include <arch/arch.hpp>
#include <boot/loader.hpp>
#include <kernel.hpp>

extern "C" void _start(void)
{
    if (!nos::boot::loader::isReady())
    {
        nos::arch::hcf();
    }

    nos::Kernel kernel;

    kernel.init();
    kernel.run();

    nos::arch::hcf();
}
