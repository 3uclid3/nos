#pragma once

#include <kernel/config.hpp>

#if NOS_ARCH_X86_64
#include <kernel/arch/x86_64/cpu.hpp>
#else
#error Unimplemented
#endif

namespace NOS::CPU {

#if NOS_ARCH_X86_64
using namespace NOS::X86_64::CPU;
#endif

} // namespace NOS::CPU
