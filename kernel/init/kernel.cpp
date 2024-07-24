#include <init/kernel.hpp>

#include <lib/log.hpp>

namespace nos {

void kernel::serial_init()
{
    _arch.serial_init();
    log::info("knos: serial port initialized");
}

void kernel::early_init()
{
    log::info("knos: early init");

    _arch.early_init();

    _pmm.init();
}

void kernel::init()
{
    log::info("knos: init");

    _arch.init();
}

void kernel::main()
{
    log::info("knos: main");

    while (true)
    {
        arch::cpu::pause();
    }
}

} // namespace nos
 