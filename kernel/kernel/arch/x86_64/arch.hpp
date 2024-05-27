#pragma once

#include <kernel/arch/x86_64/cpu/cpu.hpp>

namespace nos::x86_64 {

class arch
{
public:
    void early_init();
    void init();

public:
    [[noreturn]] static void halt(bool ints = true);
    static void pause();

private:
    cpu _cpu;
};

} // namespace nos::x86_64