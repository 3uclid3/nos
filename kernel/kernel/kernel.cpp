#include <kernel/kernel.hpp>

#include <kernel/log.hpp>

namespace nos {

void kernel::serial_init()
{
    _arch.serial_init();
}

void kernel::early_init()
{
    _arch.early_init();
    
    _physical_memory.init();
    
    log::info("kernel: early initialized");
}

void kernel::init()
{
    _arch.init();
    
    log::info("kernel: initialized");
}

void kernel::main()
{
    log::info("kernel: main");

    while (true)
    {
        arch::cpu::pause();
    }
}

} // namespace nos