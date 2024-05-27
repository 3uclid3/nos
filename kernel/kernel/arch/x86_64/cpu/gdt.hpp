#pragma once

#include <kernel/def.hpp>

namespace nos::x86_64::gdt {

enum class selector
{
    null = 0x00,
    code = 0x08,
    data = 0x10,
    user_code = 0x18,
    user_data = 0x20,
    tss = 0x28
};

struct NOS_PACKED ptr
{
    u16_t size;
    u64_t offset;
};

struct NOS_PACKED entry
{
    u16_t limit0;
    u16_t base0;
    u8_t base1;
    u8_t access;
    u8_t granularity;
    u8_t base2;
};

namespace tss {

struct NOS_PACKED ptr
{
    u32_t reserved0;
    u64_t rsp[3];
    u64_t reserved1;
    u64_t ist[7];
    u64_t reserved2;
    u16_t reserved3;
    u16_t iopb_offset;
};

struct NOS_PACKED entry
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

} // namespace tss
} // namespace nos::x86_64::gdt
