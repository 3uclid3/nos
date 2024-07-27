#include <init/kernel.hpp>

#include <cxx/cxa.hpp>
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
    _heap.init(_pmm);

    cxa::init();
}

void kernel::init()
{
    log::info("knos: init");

    _arch.init();
}

void kernel::main()
{
    log::info("knos: main");

    int* ptr = new int(42);

    delete ptr;

    while (true)
    {
        arch::cpu::pause();
    }
}

} // namespace nos
