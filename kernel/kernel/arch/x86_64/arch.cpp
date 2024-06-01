#include <kernel/arch/x86_64/arch.hpp>

#include <kernel/arch/x86_64/drivers/com-port-logger.hpp>
#include <kernel/cxx/cxxabi.hpp>
#include <kernel/utility/log.hpp>

namespace nos::x86_64 {

void arch::early_init()
{
    log::add_logger<com_port_logger>().init(standard_com_port::com1);

    cxxabi::init();

    _cpu.early_init();
}

void arch::init()
{
    _cpu.init();
}

void arch::halt(bool ints)
{
    // if (ints)
    //{
    //     while (true)
    //     {
    //         asm volatile("hlt");
    //     }
    // }
    // else
    //{
    //     while (true)
    //     {
    //         asm volatile("cli; hlt");
    //     }
    // }
}

} // namespace nos::x86_64