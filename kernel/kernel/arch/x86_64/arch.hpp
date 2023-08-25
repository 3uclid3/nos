#pragma once

#include <kernel/arch/x86_64/gdt.hpp>
#include <kernel/arch/x86_64/idt.hpp>
#include <kernel/arch/x86_64/isr.hpp>
#include <kernel/arch/x86_64/pic.hpp>
#include <kernel/arch/x86_64/tss.hpp>

namespace NOS::X86_64 {

class Arch
{
public:
    void initialize();

private:
    GDT _gdt;
    TSS _tss;
    IDT _idt;
    ISR _isr;
    PIC _pic;
};

} // namespace NOS::X86_64
