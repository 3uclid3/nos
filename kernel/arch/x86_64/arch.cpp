#include <arch/x86_64/arch.hpp>

#include <arch/x86_64/cpu/interrupt.hpp>
#include <arch/x86_64/drivers/com_port_log_sink.hpp>
#include <lib/log.hpp>

namespace nos::x86_64 {

void arch::serial_init()
{
    log::add_sink<com_port_log_sink>().init(standard_com_port::com1);
}

void arch::early_init()
{
    _cpu.early_init();
}

void arch::init()
{
    _cpu.init();
}

void arch::halt()
{
    interrupt::halt();
}

void arch::hcf()
{
    interrupt::hcf();
}

} // namespace nos::x86_64
