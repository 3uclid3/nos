#pragma once

#include <kernel/arch/x86_64/cpu/cpu.hpp>

namespace nos::x86_64 {

class arch
{
public:
    using cpu = x86_64::cpu;

public:
    void early_init();
    void init();

public:
    static void halt();
    static void hcf();

private:
    cpu _cpu;
};

} // namespace nos::x86_64