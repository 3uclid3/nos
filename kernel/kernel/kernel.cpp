#include <kernel/kernel.hpp>

#include <kernel/arch/arch.hpp>
#include <kernel/drivers/serial.hpp>
#include <kernel/lang/cxxabi.hpp>
#include <kernel/utility/log.hpp>

namespace NOS::Kernel {

void initialize()
{
    Serial::initializePorts({Serial::Ports[0]});

    Log::info("Kernel initialization");

    Log::info("\t - cxxabi");
    Lang::CxxAbi::init();

    Log::info("\t - arch");
    Arch::initialize();

    Log::info("Kernel completed");
}

void run()
{
}

} // namespace NOS::Kernel
