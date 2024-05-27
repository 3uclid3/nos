#pragma once

#include <kernel/def.hpp>

#include NOS_INCLUDE_KERNEL_ARCH(arch.hpp)

namespace nos {

class arch : public current_arch::arch
{
    using super = current_arch::arch;

public:
    void early_init();
};

} // namespace nos
