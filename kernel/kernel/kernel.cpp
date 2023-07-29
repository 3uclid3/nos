#include <kernel/kernel.hpp>

#include <kernel/arch/arch.hpp>
#include <kernel/arch/interrupt.hpp>
#include <kernel/drivers/serial.hpp>
#include <kernel/lang/cxxabi.hpp>
#include <kernel/utility/log.hpp>

namespace NOS::Kernel {

void initialize()
{
    Serial::initializePorts({Serial::Ports[0]});

    Log::info("kernel: initialization");

    {
        Log::ScopeIndent indent{1};

        Lang::CxxAbi::initialize();

        Arch::initialize();
    }

    Log::info("kernel: initialization completed");
}

void run()
{
    Interrupt::halt();
}

} // namespace NOS::Kernel
