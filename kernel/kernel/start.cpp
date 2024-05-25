#include <nxx/def.hpp>
#include <kernel/drivers/serial.hpp>

extern "C" void _start(void)
{
    nos::serial::early_init();

    while (1)
    {
        __asm__ __volatile__("hlt");
    }
}