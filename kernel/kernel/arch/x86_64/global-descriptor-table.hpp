#pragma once

#include <kernel/arch/x86_64/task-state-segment.hpp>
#include <ncxx/basic-types.hpp>

namespace NOS::X86_64 {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"

class NOS_PACKED GlobalDescriptorTable
{
public:
    struct Selector
    {
        static constexpr u8_t Null = 0x00;
        static constexpr u8_t Code = 0x08;
        static constexpr u8_t Data = 0x10;
        static constexpr u8_t UserCode = 0x18;
        static constexpr u8_t UserData = 0x20;
        static constexpr u8_t TSS = 0x28;
    };

    struct NOS_PACKED Entry
    {
        u16_t limit0;
        u16_t base0;
        u8_t base1;
        u8_t access;
        u8_t granularity;
        u8_t base2;
    };

    struct NOS_PACKED Register
    {
        u16_t size;
        u64_t offset;
    };

public:
    GlobalDescriptorTable();

    void load(const TaskStateSegment& tss);

private:
    [[nodiscard]] Register getRegister() const;

private:
    Entry _null;
    Entry _code;
    Entry _data;
    Entry _userCode;
    Entry _userData;
    TaskStateSegment::Entry _taskStateSegment;
};

#pragma clang diagnostic pop

} // namespace NOS
