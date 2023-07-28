#include <kernel/arch/x86_64/cpu/gdt.hpp>

#include <kernel/arch/x86_64/cpu/tss.hpp>
#include <ncxx/container/static-array.hpp>
#include <ncxx/def.hpp>

namespace NOS::Arch::GDT {

namespace {

// static TSS tss;

struct NOS_PACKED Entry
{
    u16_t limit;
    u16_t base0;
    u8_t base1;
    u8_t access;
    u8_t granularity;
    u8_t base2;
};
/*
struct NOS_PACKED Table
{
    Entry null{
        .limit = 0,
        .base0 = 0,
        .base1 = 0,
        .access = 0,
        .granularity = 0,
        .base2 = 0};

    Entry kernelCode{
        .limit = 0,
        .base0 = 0,
        .base1 = 0,
        .access = 0b10011010,
        .granularity = 0b00100000,
        .base2 = 0};

    Entry kernelData{
        .limit = 0,
        .base0 = 0,
        .base1 = 0,
        .access = 0b10010010,
        .granularity = 0,
        .base2 = 0};

    Entry userCode{
        .limit = 0,
        .base0 = 0,
        .base1 = 0,
        .access = 0b11111010,
        .granularity = 0b00100000,
        .base2 = 0};

    Entry userData{
        .limit = 0,
        .base0 = 0,
        .base1 = 0,
        .access = 0b11110010,
        .granularity = 0,
        .base2 = 0};

    TSS::Entry tss;
};
*/
} // namespace

void initialize()
{
}

} // namespace NOS::Arch::GDT