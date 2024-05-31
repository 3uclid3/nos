#pragma once

#include <kernel/arch/x86_64/cpu/gdt.hpp>
#include <kernel/arch/x86_64/cpu/idt.hpp>

namespace nos::x86_64 {

class cpu
{
public:
    void early_init();
    void init();
    
public:
    static void pause();

private:
    gdt _gdt;
    idt _idt;
};

} // namespace nos::x86_64
