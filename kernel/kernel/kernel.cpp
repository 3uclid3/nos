#include <kernel/kernel.hpp>

#include <kernel/arch/arch.hpp>
#include <kernel/arch/interrupt.hpp>
#include <kernel/drivers/serial.hpp>
#include <kernel/lang/cxxabi.hpp>
#include <kernel/utility/log.hpp>

namespace NOS {

void Kernel::initialize()
{
    Serial::initializePorts({Serial::Ports[0]});

    Log::info("kernel: initialization");

    {
        Log::ScopeIndent indent{1};

        Lang::CxxAbi::initialize();

        _arch.initialize();
    }

    Log::info("kernel: initialization completed");
}

void Kernel::run()
{
    Interrupt::halt();
}

} // namespace NOS
