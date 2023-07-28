#pragma once

#include <kernel/config.hpp>

#if NOS_ARCH_X86_64
#include <kernel/arch/x86_64/interrupt.hpp>
#else
#error Unimplemented
#endif

namespace NOS::Interrupt {

#if NOS_ARCH_X86_64
using namespace NOS::X86_64::Interrupt;
#endif

} // namespace NOS::Interrupt
