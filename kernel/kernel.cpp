#include <kernel.hpp>

#include <klog.hpp>

namespace nos {

void kernel::serial_init()
{
    _arch.serial_init();
}

void kernel::early_init()
{
    log::info("nos: kernel early init");

    _arch.early_init();
}

void kernel::init()
{
    log::info("nos: kernel early init");

    _arch.init();

    log::info("nos: kernel initialized");
}

void kernel::main()
{
    log::info("nos: kernel main");

    while (true)
    {
        arch::cpu::pause();
    }
}

} // namespace nos
