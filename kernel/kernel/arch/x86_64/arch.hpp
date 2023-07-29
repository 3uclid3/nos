#pragma once

#include <kernel/arch/x86_64/global-descriptor-table.hpp>
#include <kernel/arch/x86_64/interrupt-descriptor-table.hpp>
#include <kernel/arch/x86_64/task-state-segment.hpp>

namespace NOS::X86_64 {

class Arch
{
public:
    void initialize();

private:
    GlobalDescriptorTable _gdt;
    TaskStateSegment _tss;
    InterruptDescriptorTable _idt;
};

} // namespace NOS::X86_64
