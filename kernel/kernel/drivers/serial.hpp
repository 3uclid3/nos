#pragma once

#include <kernel/def.hpp>

#include NOS_INCLUDE_KERNEL_ARCH(drivers/serial.hpp)

namespace nos::serial {

inline void early_init()
{
    NOS_ARCH::serial::early_init();
}

inline char read()
{
    return NOS_ARCH::serial::read();
}

inline void write(char c)
{
    NOS_ARCH::serial::write(c);
}

} // namespace nos::serial
