#include <kernel/kernel.hpp>
#include <kernel/cxx/cxa.hpp>

extern "C" void _start(void)
{
    using namespace nos;

    kernel kernel;
    kernel.serial_init();
    kernel.early_init();

    cxa::init();

    kernel.init();
    kernel.main();
}
