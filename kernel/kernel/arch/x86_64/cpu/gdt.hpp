#pragma once

#include <kernel/def.hpp>
#include <nxx/container/span.hpp>

namespace nos::x86_64 {

class gdt
{
public:
    struct selector
    {
        static constexpr u8_t null = 0x00;
        static constexpr u8_t kernel_code = 0x08;
        static constexpr u8_t kernel_data = 0x10;
        static constexpr u8_t user_code = 0x18;
        static constexpr u8_t user_data = 0x20;
        static constexpr u8_t tss = 0x28;
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

    struct tss
    {
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
    };

public:
    bool is_loaded() const;
    bool is_tss_loaded(const tss::ptr& ptr) const;

    void load(size_t i);

private:
    struct NOS_PACKED entries
    {
        entry null;
        entry kernel_code;
        entry kernel_data;
        entry user_code;
        entry user_data;
        tss::entry tss;
    };

    // TODO Support multi-core
    static_array<tss::ptr, 1> _tsses{};
    static_array<entries, 1> _entries{};
};

} // namespace nos::x86_64
