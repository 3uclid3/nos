#include <kernel/arch/x86_64/cpu/idt.hpp>

#include <kernel/arch/x86_64/cpu/gdt.hpp>
#include <kernel/arch/x86_64/utility/io.hpp>
#include <kernel/utility/log.hpp>

extern "C" void* nos_interrupt_table[];

extern "C" void nos_interrupt_handler(void* registers)
{
    (void)registers;

    nos::log::traceln("interrupt!");
}

namespace nos::x86_64 {

void idt::entry::setup(void* new_isr_ptr, uint8_t new_type_attr, uint8_t new_ist)
{
    u64_t new_isr = reinterpret_cast<u64_t>(new_isr_ptr);
    offset1 = static_cast<u16_t>(new_isr);
    selector = gdt::selector::kernel_code;
    ist = new_ist;
    type_attr = new_type_attr;
    offset2 = static_cast<u16_t>(new_isr >> 16);
    offset3 = static_cast<u32_t>(new_isr >> 32);
    zero = 0;
}

void idt::init()
{
    log::traceln("idt: init");

    for (size_t i = 0; i < _entries.size(); ++i)
    {
        _entries[i].setup(nos_interrupt_table[i]);
    }
    
    _ptr.limit = static_cast<u16_t>(sizeof(entry) * _entries.size() - 1);
    _ptr.base = reinterpret_cast<uintptr_t>(_entries.data());

    asm volatile("cli");
    asm volatile("lidt %0" ::"memory"(_ptr));
    asm volatile("sti");

    
    log::traceln("idt: init done");
}

} // namespace nos::x86_64
