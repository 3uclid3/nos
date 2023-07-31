#pragma once

#include <kernel/arch/x86_64/idt.hpp>
#include <ncxx/basic-types.hpp>
#include <ncxx/container/static-array.hpp>
#include <ncxx/functional/function.hpp>
#include <ncxx/utility/enum-string.hpp>

namespace NOS::X86_64 {

namespace CPU {
struct Registers;
} // namespace CPU

class ISR
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

    struct Handler
    {
        using Functor = Function<void(const CPU::Registers&)>;

        Functor functor;
    };

    using Handlers = StaticArray<Handler, IDT::Entries::MaximumSize>;

public:
    ISR();
    ~ISR();

    void dispatch(const CPU::Registers& registers);

private:
    void dispatchException(const CPU::Registers& registers);
    void dispatchHandler(const CPU::Registers& registers);
    void dispatchUnknown(const CPU::Registers& registers);

private:
    Handlers _handlers;
};

} // namespace NOS::X86_64
