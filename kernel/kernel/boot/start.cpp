#include <kernel/kernel.hpp>

extern "C" void _start(void)
{
    nos::kernel kernel;
    kernel.run();
}
