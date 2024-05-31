#pragma once

#include <kernel/arch/x86_64/cpu/cpu.hpp>
#include <kernel/arch/x86_64/drivers/com-port-log-printer.hpp>

namespace nos::x86_64 {

class arch
{
public:
    using cpu = x86_64::cpu;

public:
    void early_init();
    void init();

public:
    static void halt(bool ints = true);

private:
    cpu _cpu;

    com_port_log_printer _com_log_printer;
};

} // namespace nos::x86_64