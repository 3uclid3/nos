#pragma once

#include <arch/x86_64/cpu.hpp>

namespace nos::x86_64 {

class arch
{
public:
    using cpu = x86_64::cpu;

public:
    void serial_init();
    void early_init();
    void init();

public:
    static void halt();
    HEDLEY_NO_RETURN static void hcf();

private:
    cpu _cpu;
};

} // namespace nos::x86_64
