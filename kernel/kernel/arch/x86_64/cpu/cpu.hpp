#pragma once

#include <kernel/arch/x86_64/cpu/gdt.hpp>

namespace nos::x86_64 {

class cpu
{
public:
    void early_init();
    void init();

private:
    gdt _gdt;
};

} // namespace nos::x86_64
