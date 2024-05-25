#include <nxx/def.hpp>

extern "C" void _start(void)
{
    nxx::u16_t i;
    (void)i;

    while (1)
    {
        __asm__ __volatile__("hlt");
    }
}