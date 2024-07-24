#include <arch.hpp>

#include <arch/x86_64/cpu/interrupt.hpp>
#include <arch/x86_64/drivers/com_port_log_sink.hpp>
#include <klog.hpp>

namespace nos::x86_64 {

void arch::serial_init()
{
    log::add_sink<com_port_log_sink>().init(standard_com_port::com1);
    log::info("nos: com1 port initialized");
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
