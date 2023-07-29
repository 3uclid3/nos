#pragma once

#include <kernel/config.hpp>
#include NOS_INCLUDE_KERNEL_ARCH_FILE(arch.hpp)

namespace NOS {

class Arch : public NOS_KERNEL_ARCH_TYPE(Arch)
{
};

} // namespace NOS