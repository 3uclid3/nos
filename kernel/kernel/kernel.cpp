#include <kernel/kernel.hpp>

#include <kernel/log.hpp>

namespace nos {

kernel::kernel()
{
    early_init();
    init();
}

void kernel::run()
{
    while (true)
    {
        arch::cpu::pause();
    }
}

void kernel::early_init()
{
    _arch.early_init();
}

void kernel::init()
{
    log::info("kernel: init");

    _arch.init();

    log::info("kernel: init completed");
}

} // namespace nos