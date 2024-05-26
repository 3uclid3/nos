#include <kernel/def.hpp>
#include <kernel/boot/kmain.hpp>
#include <kernel/drivers/serial.hpp>
#include <kernel/cxx/cxx-abi.hpp>

extern "C" void _start(void)
{
    using namespace nos;

    serial::early_init();
    cxx_abi::init();

    kmain();
}
