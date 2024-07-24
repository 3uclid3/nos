#pragma once

#ifdef __x86_64__

#include <arch/x86_64/arch.hpp>

namespace nos {
using arch = nos::x86_64::arch;
} // namespace nos

#else

#error "Unsupported architecture"

#endif
