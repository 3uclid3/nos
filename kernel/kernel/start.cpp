#include <kernel/kernel.hpp>

extern "C" void _start(void)
{
    NOS::Kernel kernel;

    kernel.initialize();
    kernel.run();
}
