#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/preprocessor/packed.hpp>
#include <ncxx/container/static-array.hpp>
#include <ncxx/utility/enum-string.hpp>

namespace NOS::X86_64 {

namespace CPU {
struct Registers;
} // namespace CPU

class NOS_PACKED InterruptDescriptorTable
{
public:
    enum class Exception
    {
        DivisionByZero,
        Debug,
        NonMaskableInterrupt,
        Breakpoint,
        DetectedOverflow,
        OutOfBounds,
        InvalidOpCode,
        NoCoprocessor,
        DoubleFault,
        CoprocessorSegmentOverrun,
        BadTaskStateSegment,
        SegmentNotPresent,
        StackFault,
        GeneralProtectionFault,
        PageFault,
        UnknownInterrupt,
        CoprocessorFault,
        AlignmentCheck,
        MachineCheck,
        Reserved19,
        Reserved20,
        Reserved21,
        Reserved22,
        Reserved23,
        Reserved24,
        Reserved25,
        Reserved26,
        Reserved27,
        Reserved28,
        Reserved29,
        Reserved30,
        Reserved31,

        Count
    };
    static constexpr EnumString<Exception, Exception::Count> ExceptionString;

    struct NOS_PACKED Entry
    {
        u16_t offset1;
        u16_t selector;
        u8_t ist;
        u8_t typeAttr;
        u16_t offset2;
        u32_t offset3;
        u32_t zero;

        void set(void* isr_, uint8_t typeAttr_ = 0x8E, uint8_t ist_ = 0);
    };

    using Entries = StaticArray<Entry, 256>;

    struct NOS_PACKED Register
    {
        u16_t limit;
        u64_t base;
    };

public:
    InterruptDescriptorTable();

    void load();
    void dispatch(const CPU::Registers& registers);

private:
    [[nodiscard]] Register makeRegister() const;

    void handleException(const CPU::Registers& registers);

private:
    Entries _entries;
};

} // namespace NOS::X86_64
