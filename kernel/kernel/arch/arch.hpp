#pragma once

#include <nos/def.hpp>

#include NOS_INCLUDE_KERNEL_ARCH(arch.hpp)

namespace nos::arch {

inline void init()
{
    NOS_ARCH::arch::init();
}

inline void pause()
{
    NOS_ARCH::arch::pause();
}

[[noreturn]] inline void halt(bool ints = true)
{
    NOS_ARCH::arch::halt(ints);
}

} // namespace nos::arch
