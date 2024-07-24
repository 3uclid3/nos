#include <arch/x86_64/cpu/idt.hpp>

#include <cassert>
#include <type_traits>

#include <magic_enum.hpp>

#include <arch/x86_64/cpu/cpu_registers.hpp>
#include <arch/x86_64/cpu/gdt.hpp>
#include <arch/x86_64/cpu/interrupt.hpp>
#include <lib/log.hpp>

namespace nos::x86_64::details {
idt* active_idt{nullptr};
} // namespace nos::x86_64::details

HEDLEY_C_DECL void* nos_interrupt_table[];

HEDLEY_C_DECL void nos_interrupt_handler(nos::x86_64::cpu_registers* registers)
{
    nos::x86_64::details::active_idt->dispatch_interrupt(*registers);
}

namespace nos::x86_64 {

namespace details {

enum class exception
{
    division_by_zero,
    debug,
    non_maskable_interrupt,
    breakpoint,
    detected_overflow,
    out_of_bounds,
    invalid_op_code,
    no_coprocessor,
    double_fault,
    coprocessor_segment_overrun,
    bad_task_state_segment,
    segment_not_present,
    stack_fault,
    general_protection_fault,
    page_fault,
    unknown_interrupt,
    coprocessor_fault,
    alignment_check,
    machine_check,
    reserved19,
    reserved20,
    reserved21,
    reserved22,
    reserved23,
    reserved24,
    reserved25,
    reserved26,
    reserved27,
    reserved28,
    reserved29,
    reserved30,
    reserved31,

    count
};

void log_error_registers(const cpu_registers& registers)
{
    log::error("nos: registers");

    // clang-format off
    log::error("nos: r8=0x{:X} r9=0x{:X} r10=0x{:X} r11=0x{:X} r12=0x{:X} r13=0x{:X} r14=0x{:X} r15=0x{:X}",
                    registers.r8, registers.r9, registers.r10, registers.r11, registers.r12, registers.r13, registers.r14, registers.r15);

    log::error("nos: rax=0x{:X} rbx=0x{:X} rcx=0x{:X} rdx=0x{:X} rsi=0x{:X} rdi=0x{:X} rbp=0x{:X}",
                    registers.rax, registers.rbx, registers.rcx, registers.rdx, registers.rsi, registers.rdi, registers.rbp);

    log::error("nos: interrupt=0x{:X} error code=0x{:X}",
                    registers.interrupt, registers.error_code);
    // clang-format on
}

} // namespace details

void idt::entry::setup(void* new_isr_ptr, std::uint8_t new_type_attr, std::uint8_t new_ist)
{
    std::uint64_t new_isr = reinterpret_cast<std::uint64_t>(new_isr_ptr);
    offset1 = static_cast<std::uint16_t>(new_isr);
    selector = gdt::selector::kernel_code;
    ist = new_ist;
    type_attr = new_type_attr;
    offset2 = static_cast<std::uint16_t>(new_isr >> 16);
    offset3 = static_cast<std::uint32_t>(new_isr >> 32);
    zero = 0;
}

void idt::init()
{
    log::info("nos: idt init");

    assert(details::active_idt == nullptr);
    details::active_idt = this;

    for (size_t i = 0; i < _entries.size(); ++i)
    {
        _entries[i].setup(nos_interrupt_table[i]);
    }

    load();
}

void idt::load()
{
    ptr ptr;
    ptr.limit = static_cast<std::uint16_t>(sizeof(entry) * _entries.size() - 1);
    ptr.base = reinterpret_cast<uintptr_t>(_entries.data());

    interrupt::disable();
    asm volatile("lidt %0" ::"memory"(ptr));
    interrupt::enable();
}

void idt::dispatch_interrupt(const cpu_registers& registers)
{
    const auto exception_count = std::to_underlying(details::exception::count);

    if (registers.interrupt < exception_count)
    {
        dispatch_exception(registers);
    }
    else if (registers.interrupt < _handlers.size())
    {
        dispatch_handler(registers);
    }
    else
    {
        dispatch_unknown(registers);
    }
}

void idt::dispatch_exception(const cpu_registers& registers)
{
    log::error("nos: idt exception interrupt {} on CPU {}", magic_enum::enum_name(static_cast<details::exception>(registers.interrupt)), 0);

    details::log_error_registers(registers);

    // TODO Panic

    interrupt::hcf();
}

void idt::dispatch_handler(const cpu_registers& registers)
{
    log::info("nos: idt interrupt {} on CPU {}", registers.interrupt, 0);

    if (_handlers[registers.interrupt])
    {
        _handlers[registers.interrupt](registers);
    }
    else
    {
        log::error("nos: idt unimplemented interrupt");

        details::log_error_registers(registers);

        // TODO Panic ?
    }
}

void idt::dispatch_unknown(const cpu_registers& registers)
{
    log::error("nos: idt unknown interrupt {:X} on CPU {}", registers.interrupt, 0);

    details::log_error_registers(registers);

    // TODO Panic
}

} // namespace nos::x86_64
