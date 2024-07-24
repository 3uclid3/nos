#include <arch/x86_64/cpu/gdt.hpp>

#include <type_traits>

#include <lib/log.hpp>

namespace nos::x86_64 {

bool gdt::is_loaded() const
{
    std::uint16_t kernel_data = selector::kernel_data;
    std::uint16_t value{0};

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
    log::info("nos: gdt loading (core={})", i);

    const std::uint64_t base = reinterpret_cast<std::uint64_t>(&_tsses[i]);
    const std::uint16_t limit = sizeof(tss::entry);

    entries& current_entries = _entries[i];

    current_entries.null = {0x000, 0, 0, 0x00, 0x00, 0};
    current_entries.kernel_code = {0x0000, 0, 0, 0x9A, 0x20, 0};
    current_entries.kernel_data = {0x0000, 0, 0, 0x92, 0x00, 0};
    current_entries.user_code = {0x0000, 0, 0, 0xF2, 0x00, 0};
    current_entries.user_data = {0x0000, 0, 0, 0xFA, 0x20, 0};
    current_entries.tss = {
        limit,
        static_cast<std::uint16_t>(base),
        static_cast<std::uint8_t>(base >> 16),
        0x89,
        0x00,
        static_cast<std::uint8_t>(base >> 24),
        static_cast<std::uint16_t>(base >> 32),
        0x00};

    ptr gdtr{
        sizeof(entries) - 1,
        reinterpret_cast<std::uint64_t>(&current_entries)};

    log::info("nos: gdt init");
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

    log::info("nos: gdt setup");
    asm volatile("ltr %0" ::"r"(static_cast<std::uint16_t>(selector::tss)));

    log::info("nos: gdt validate loading (core={})", i);

    assert(is_loaded());

    log::info("nos: gdt loadend (core={})", i);
}

} // namespace nos::x86_64
