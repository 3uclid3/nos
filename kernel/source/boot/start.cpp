#include <arch/arch.hpp>
#include <boot/loader.hpp>
#include <drivers/serial.hpp>
#include <kernel.hpp>
#include <utility/log.hpp>

namespace NOS {

void start()
{
    Serial::earlyInitialize(Serial::Port::COM1);

    Log::info("Early initialization completed successfully");
}

} // namespace NOS

extern "C" void _start(void)
{
    NOS::start();
}
