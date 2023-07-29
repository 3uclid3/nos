#include <kernel/arch/x86_64/global-descriptor-table.hpp>

#include <kernel/utility/log.hpp>

namespace NOS::X86_64 {

GlobalDescriptorTable::GlobalDescriptorTable()
    : _null({.limit0 = 0x0000, .base0 = 0, .base1 = 0, .access = 0x00, .granularity = 0x00, .base2 = 0})
    , _code({0x0000, 0, 0, 0x9A, 0x20, 0})
    , _data({0x0000, 0, 0, 0x92, 0x00, 0})
    , _userCode({0x0000, 0, 0, 0xF2, 0x00, 0})
    , _userData({0x0000, 0, 0, 0xFA, 0x20, 0})
    , _taskStateSegment({.size = sizeof(TaskStateSegment), .base0 = 0, .base1 = 0, .flags1 = 0x89, .flags2 = 0, .base2 = 0, .base3 = 0, .reserved = 0})
{
}

void GlobalDescriptorTable::load(const TaskStateSegment& tss)
{
    Log::info("gdt: loading");

    _taskStateSegment.setPointer(tss);

    Register r = getRegister();

    asm volatile(
        "lgdt %[gdtr]\n\t"
        "mov %[dsel], %%ds \n\t"
        "mov %[dsel], %%fs \n\t"
        "mov %[dsel], %%gs \n\t"
        "mov %[dsel], %%es \n\t"
        "mov %[dsel], %%ss \n\t"
        "push %[csel] \n\t"
        "lea 1f(%%rip), %%rax \n\t"
        "push %%rax \n\t"
        ".byte 0x48, 0xCB \n"
        "1:" ::[gdtr] "m"(r),
        [dsel] "m"(Selector::Data),
        [csel] "i"(Selector::Code)
        : "rax", "memory");

    asm volatile("ltr %0" ::"r"(static_cast<u16_t>(Selector::TSS)));
}

GlobalDescriptorTable::Register GlobalDescriptorTable::getRegister() const
{
    return {sizeof(GlobalDescriptorTable) - 1, reinterpret_cast<uintptr_t>(this)};
}

} // namespace NOS::X86_64
