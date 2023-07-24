#include <kernel.hpp>

extern "C" void _start(void)
{
    NOS::Kernel::initialize();
    NOS::Kernel::run();
}
