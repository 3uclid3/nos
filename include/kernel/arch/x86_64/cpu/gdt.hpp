#pragma once

#include <array>
#include <cstdint>

#include <kdef.hpp>

namespace nos::x86_64 {

class gdt
{
public:
    struct selector
    {
        static constexpr std::uint8_t null = 0x00;
        static constexpr std::uint8_t kernel_code = 0x08;
        static constexpr std::uint8_t kernel_data = 0x10;
        static constexpr std::uint8_t user_code = 0x18;
        static constexpr std::uint8_t user_data = 0x20;
        static constexpr std::uint8_t tss = 0x28;
    };

    struct NOS_PACKED ptr
    {
        std::uint16_t size;
        std::uint64_t offset;
    };

    struct NOS_PACKED entry
    {
        std::uint16_t limit0;
        std::uint16_t base0;
        std::uint8_t base1;
        std::uint8_t access;
        std::uint8_t granularity;
        std::uint8_t base2;
    };

    struct tss
    {
        struct NOS_PACKED ptr
        {
            std::uint32_t reserved0;
            std::uint64_t rsp[3];
            std::uint64_t reserved1;
            std::uint64_t ist[7];
            std::uint64_t reserved2;
            std::uint16_t reserved3;
            std::uint16_t iopb_offset;
        };

        struct NOS_PACKED entry
        {
            std::uint16_t length;
            std::uint16_t base0;
            std::uint8_t base1;
            std::uint8_t flags1;
            std::uint8_t flags2;
            std::uint8_t base2;
            std::uint32_t base3;
            std::uint32_t reserved;
        };
    };

public:
    bool is_loaded() const;
    bool is_tss_loaded(const tss::ptr& ptr) const;

    void load(std::size_t i);

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
    std::array<tss::ptr, 1> _tsses{};
    std::array<entries, 1> _entries{};
};

} // namespace nos::x86_64
