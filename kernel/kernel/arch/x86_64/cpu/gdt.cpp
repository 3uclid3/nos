#include <kernel/arch/x86_64/cpu/gdt.hpp>

#include <kernel/log.hpp>
#include <nxx/type_trait/underlying_type.hpp>

namespace nos::x86_64 {

bool gdt::is_loaded() const
{
    u16_t kernel_data = selector::kernel_data;
    u16_t value{0};

    asm volatile(
        "movw %1, %%ds\n\t" // Load data segment selector into DS
        "movw %%ds, %0\n\t" // Move DS value into ds_value
        : "=r"(value)       // Output
        : "r"(kernel_data)  // Input
        : "memory"          // Clobber list
    );

    return value == selector::kernel_data;
}

void gdt::load(size_t i)
{
    log::info("gdt: load core {}", i);

    const u64_t base = reinterpret_cast<u64_t>(&_tsses[i]);
    const u16_t limit = sizeof(tss::entry);

    entries& current_entries = _entries[i];

    current_entries.null = {0x000, 0, 0, 0x00, 0x00, 0};
    current_entries.kernel_code = {0x0000, 0, 0, 0x9A, 0x20, 0};
    current_entries.kernel_data = {0x0000, 0, 0, 0x92, 0x00, 0};
    current_entries.user_code = {0x0000, 0, 0, 0xF2, 0x00, 0};
    current_entries.user_data = {0x0000, 0, 0, 0xFA, 0x20, 0};
    current_entries.tss = {
        limit,
        static_cast<u16_t>(base),
        static_cast<u8_t>(base >> 16),
        0x89,
        0x00,
        static_cast<u8_t>(base >> 24),
        static_cast<u16_t>(base >> 32),
        0x00};

    ptr gdtr{
        sizeof(entries) - 1,
        reinterpret_cast<u64_t>(&current_entries)};

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
        "1:" ::[gdtr] "m"(gdtr),
        [dsel] "m"(selector::kernel_data),
        [csel] "i"(selector::kernel_code)
        : "rax", "memory");

    asm volatile("ltr %0" ::"r"(static_cast<u16_t>(selector::tss)));

    NOS_ASSERT(is_loaded());
}

} // namespace nos::x86_64