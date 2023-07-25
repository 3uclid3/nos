#include <kernel.hpp>

#include <drivers/serial.hpp>
#include <lang/cxxabi.hpp>
#include <utility/log.hpp>

namespace NOS::Kernel {

void initialize()
{
    Serial::earlyInitialize(Serial::Port::COM1); // Required for Log

    Log::info("Kernel initialization");

    Log::info("\t - cxxabi");
    Lang::CxxAbi::init();
}

void run()
{
}

} // namespace NOS::Kernel
