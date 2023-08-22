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
    Serial::initializePorts({Serial::Ports[0]});

    Lang::CxxAbi::initialize();

    X86_64::IO::out(X86_64::IO::Port::Debug, u8_t{'D'});

    auto ptr = makeUnique<Log::SerialSink>();
    
    X86_64::IO::out(X86_64::IO::Port::Debug, u8_t{'G'});

    Log::addSink(move(ptr));

    X86_64::IO::out(X86_64::IO::Port::Debug, u8_t{'S'});

    Log::info(this).message("initialization");

    _arch.initialize();

    Log::info(this).message("initialization completed");
}

void Kernel::run()
{
    Interrupt::halt();
}

} // namespace NOS
