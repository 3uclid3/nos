#include <kernel/arch/x86_64/arch.hpp>

#include <kernel/cxx/cxxabi.hpp>

namespace nos::x86_64 {

void arch::early_init()
{
    _com_log_printer.init(standard_com_port::com1);

    log::set_printer(_com_log_printer);

    cxxabi::init();

    _cpu.early_init();
}

void arch::init()
{
    _cpu.init();
}

void arch::halt(bool ints)
{
    //if (ints)
    //{
    //    while (true)
    //    {
    //        asm volatile("hlt");
    //    }
    //}
    //else
    //{
    //    while (true)
    //    {
    //        asm volatile("cli; hlt");
    //    }
    //}
}

} // namespace nos::x86_64