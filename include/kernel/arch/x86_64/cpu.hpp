#pragma once

#include <arch/x86_64/cpu/gdt.hpp>
#include <arch/x86_64/cpu/idt.hpp>
#include <arch/x86_64/cpu/pic.hpp>

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
    pic _pic;
};

} // namespace nos::x86_64
