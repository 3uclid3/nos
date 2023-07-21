#include <arch/arch.hpp>
#include <boot/loader.hpp>
#include <kernel.hpp>

extern "C" void _start(void)
{
    if (!NOS::Boot::Loader::isReady())
    {
        NOS::Arch::hcf();
    }

    NOS::Kernel kernel;

    kernel.init();
    kernel.run();

    NOS::Arch::hcf();
}
