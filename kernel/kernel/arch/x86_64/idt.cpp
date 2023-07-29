#include <kernel/arch/x86_64/idt.hpp>

#include <kernel/arch/x86_64/cpu.hpp>
#include <kernel/arch/x86_64/gdt.hpp>
#include <kernel/utility/log.hpp>
#include <kernel/utility/panic.hpp>
#include <ncxx/basic-types.hpp>
#include <ncxx/container/static-array.hpp>
#include <ncxx/preprocessor/packed.hpp>
#include <ncxx/string/format.hpp>
#include <ncxx/string/string-view.hpp>

extern "C" void* NOS_interruptTable[];

namespace NOS::X86_64::IDT {

inline constexpr size_t MaximumEntries = 256;

namespace Data {

struct NOS_PACKED Entry
{
    u16_t offset1;
    u16_t selector;
    u8_t ist;
    u8_t typeAttr;
    u16_t offset2;
    u32_t offset3;
    u32_t zero{0};

    void set(void* isr_, uint8_t typeAttr_ = 0x8E, uint8_t ist_ = 0)
    {
        u64_t isr = reinterpret_cast<u64_t>(isr_);
        offset1 = static_cast<u16_t>(isr);
        selector = GDT::Selector::Code;
        ist = ist_;
        typeAttr = typeAttr_;
        offset2 = static_cast<u16_t>(isr >> 16);
        offset3 = static_cast<u32_t>(isr >> 32);
    }
};

struct NOS_PACKED Register
{
    u16_t limit;
    u64_t base;

    void load()
    {
        asm volatile("cli");
        asm volatile("lidt %0" ::"memory"(*this));
        asm volatile("sti");
    }
};

StaticArray<Entry, MaximumEntries> entries;

Register idtr{
    .limit = sizeof(Entry) * MaximumEntries - 1,
    .base = reinterpret_cast<uintptr_t>(entries.data())};

} // namespace Data

constexpr StringView ExceptionMessages[32]{
    "Division by zero",
    "Debug",
    "Non-maskable interrupt",
    "Breakpoint",
    "Detected overflow",
    "Out-of-bounds",
    "Invalid opcode",
    "No coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt",
    "Coprocessor fault",
    "Alignment check",
    "Machine check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

void handleException(const CPU::Registers& registers)
{
    panic(format("idt: Exception {} on CPU {}", ExceptionMessages[registers.interrupt], 0));
}

void dispatch(const CPU::Registers& registers)
{
    Log::info("idt: dispatch");

    if (registers.interrupt < 32)
    {
        handleException(registers);
    }
    else if (registers.interrupt >= 32 && registers.interrupt <= MaximumEntries)
    {
    }
    else
    {
        panic(format("idt: Unknown interrupt {}", ExceptionMessages[registers.interrupt], 0));
    }
}

void initialize()
{
    Log::info("idt: initialization");

    for (size_t i = 0; i < Data::entries.size(); ++i)
    {
        Data::entries[i].set(NOS_interruptTable[i]);
    }

    Data::idtr.load();
}

} // namespace NOS::X86_64::IDT

extern "C" void NOS_interruptHandler(NOS::X86_64::CPU::Registers* registers)
{
    NOS::X86_64::IDT::dispatch(*registers);
}
