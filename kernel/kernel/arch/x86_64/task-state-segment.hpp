#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/preprocessor/packed.hpp>

namespace NOS {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"

class NOS_PACKED TaskStateSegment
{
public:
    struct NOS_PACKED Entry
    {
        u16_t size;
        u16_t base0;
        u8_t base1;
        u8_t flags1;
        u8_t flags2;
        u8_t base2;
        u32_t base3;
        u32_t reserved;

        void setPointer(const TaskStateSegment& tss);
    };

    struct NOS_PACKED Register
    {
        u16_t size;
        u64_t offset;
    };

private:
    u32_t _reserved0;
    u64_t _rsp0;
    u64_t _rsp1;
    u64_t _rsp2;
    u64_t _reserved1;
    u64_t _ist0;
    u64_t _ist1;
    u64_t _ist2;
    u64_t _ist3;
    u64_t _ist4;
    u64_t _ist5;
    u64_t _ist6;
    u64_t _ist7;
    u64_t _reserved2;
    u16_t _reserved3;
    u16_t _iopbOffset;
};

#pragma clang diagnostic pop

} // namespace NOS
