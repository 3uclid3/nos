#pragma once

#include <kernel/config.hpp>

#if NOS_ARCH_X86_64
#include <kernel/arch/x86_64/drivers/serial.hpp>
#endif

namespace NOS::Serial {

#if NOS_ARCH_X86_64
using namespace NOS::X86_64::Serial;
#endif

} // namespace NOS::Serial
