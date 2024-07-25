#pragma once

#include <kdef.hpp>

namespace nos::x86_64::interrupt {

inline void enable()
{
    asm volatile("sti");
}

inline void disable()
{
    asm volatile("cli");
}

inline void halt()
{
    asm volatile("hlt");
}

[[noreturn]] inline void hcf()
{
    while (true)
    {
        asm volatile("cli; hlt");
    }
}

} // namespace nos::x86_64::interrupt
