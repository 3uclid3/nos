#include <kernel/kernel.hpp>

#include <kernel/arch/arch.hpp>
#include <kernel/arch/interrupt.hpp>
#include <kernel/drivers/serial.hpp>
#include <kernel/lang/cxxabi.hpp>
#include <kernel/log/serial-sink.hpp>
#include <log/log.hpp>

#include <kernel/arch/x86_64/io.hpp>

namespace NOS {

void Kernel::initialize()
{
    Lang::CxxAbi::initialize();

    Serial::initializePorts({Serial::Ports[0]});

    Log::addSink(makeUnique<Log::SerialSink>());
    Log::info(this).message("initialization");

    _arch.initialize();
}

void Kernel::run()
{
    Interrupt::halt();
}

} // namespace NOS
