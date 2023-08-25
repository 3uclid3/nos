#include <kernel/arch/x86_64/isr.hpp>

#include <kernel/arch/x86_64/cpu.hpp>
#include <kernel/arch/x86_64/interrupt.hpp>
#include <kernel/utility/panic.hpp>
#include <log/log.hpp>
#include <ncxx/utility/to-underlying-type.hpp>

namespace NOS::X86_64 {

namespace {

// Used by function NOS_interruptHandler called from asm
struct GlobalInstance
{
    inline static ISR* isr{nullptr};
};

void logRegisters(const CPU::Registers& registers)
{
    Log::error<ISR>().message("registers");

    // clang-format off
    Log::error<ISR>().format("r8=0x{:X} r9=0x{:X} r10=0x{:X} r11=0x{:X} r12=0x{:X} r13=0x{:X} r14=0x{:X} r15=0x{:X}",
                    registers.r8, registers.r9, registers.r10, registers.r11, registers.r12, registers.r13, registers.r14, registers.r15);
    Log::error<ISR>().format("rax=0x{:X} rbx=0x{:X} rcx=0x{:X} rdx=0x{:X} rsi=0x{:X} rdi=0x{:X} rbp=0x{:X}",
                    registers.rax, registers.rbx, registers.rcx, registers.rdx, registers.rsi, registers.rdi, registers.rbp);
    Log::error<ISR>().format("interrupt=0x{:X} error code=0x{:X}",
                    registers.interrupt, registers.errorCode);
    // clang-format on
}

} // namespace

ISR::ISR()
{
    NOS_ASSERT(GlobalInstance::isr == nullptr);
    GlobalInstance::isr = this;
}

ISR::~ISR()
{
    NOS_ASSERT(GlobalInstance::isr == this);
    GlobalInstance::isr = nullptr;
}

void ISR::dispatch(const CPU::Registers& registers)
{
    const auto exceptionCount = toUnderlyingType(Exception::Count);

    if (registers.interrupt < exceptionCount)
    {
        dispatchException(registers);
    }
    else if (registers.interrupt < _handlers.size())
    {
        dispatchHandler(registers);
    }
    else
    {
        dispatchUnknown(registers);
    }
}

void ISR::dispatchException(const CPU::Registers& registers)
{
    Log::error(this).format("Exception interrupt {} on CPU {}", ExceptionString[registers.interrupt], 0);

    logRegisters(registers);

    panic();
}

void ISR::dispatchHandler(const CPU::Registers& registers)
{
    Log::info(this).format("Interrupt {} on CPU {}", registers.interrupt, 0);

    _handlers[registers.interrupt].functor(registers);
}

void ISR::dispatchUnknown(const CPU::Registers& registers)
{
    Log::error(this).format("Unknown interrupt {} on CPU {}", registers.interrupt, 0);

    logRegisters(registers);

    panic();
}

} // namespace NOS::X86_64

extern "C" void NOS_interruptHandler(NOS::X86_64::CPU::Registers* registers)
{
    NOS::X86_64::GlobalInstance::isr->dispatch(*registers);
}