#include <kernel/arch/x86_64/gdt.hpp>

#include <ncxx/basic-types.hpp>
#include <ncxx/preprocessor/packed.hpp>

namespace NOS::X86_64::GDT {

namespace Data {

struct NOS_PACKED GDTR
{
    u16_t size;
    u64_t offset;
};

struct NOS_PACKED GDTEntry
{
    u16_t limit0;
    u16_t base0;
    u8_t base1;
    u8_t access;
    u8_t granularity;
    u8_t base2;
};

struct NOS_PACKED TSSEntry
{
    u16_t length;
    u16_t base0;
    u8_t base1;
    u8_t flags1;
    u8_t flags2;
    u8_t base2;
    u32_t base3;
    u32_t reserved;
};

struct NOS_PACKED GDT
{
    GDTEntry null;
    GDTEntry code;
    GDTEntry data;
    GDTEntry userCode;
    GDTEntry userData;
    TSSEntry tss;
};

struct NOS_PACKED TSS
{
    u32_t reserved0;
    u64_t rsp[3];
    u64_t reserved1;
    u64_t ist[7];
    u64_t reserved2;
    u16_t reserved3;
    u16_t iopboffset;
};

TSS tss;
GDT gdt{
    {0x0000, 0, 0, 0x00, 0x00, 0}, // Null
    {0x0000, 0, 0, 0x9A, 0x20, 0}, // Code
    {0x0000, 0, 0, 0x92, 0x00, 0}, // Data
    {0x0000, 0, 0, 0xF2, 0x00, 0}, // User data
    {0x0000, 0, 0, 0xFA, 0x20, 0}, // User code
    {
        sizeof(TSS),
        static_cast<u16_t>(reinterpret_cast<uintptr_t>(&tss)),
        static_cast<u8_t>(reinterpret_cast<uintptr_t>(&tss) >> 16),
        0x89,
        0x00,
        static_cast<u8_t>(reinterpret_cast<uintptr_t>(&tss) >> 24),
        static_cast<u32_t>(reinterpret_cast<uintptr_t>(&tss) >> 32),
        0x00} // Tss
};

GDTR gdtr{
    sizeof(GDT) - 1,
    reinterpret_cast<uintptr_t>(&gdt),
};

} // namespace Data

void initialize()
{
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
        "1:" ::[gdtr] "m"(Data::gdtr),
        [dsel] "m"(Selector::Data),
        [csel] "i"(Selector::Code)
        : "rax", "memory");
    asm volatile("ltr %0" ::"r"(static_cast<u16_t>(Selector::TSS)));
}

} // namespace NOS::X86_64::GDT
