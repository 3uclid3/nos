#pragma once

#include <kdef.hpp>

namespace nos::x86_64::interrupt {

HEDLEY_INLINE void enable()
{
    asm volatile("sti");
}

HEDLEY_INLINE void disable()
{
    asm volatile("cli");
}

HEDLEY_INLINE void halt()
{
    asm volatile("hlt");
}

HEDLEY_NO_RETURN HEDLEY_INLINE void hcf()
{
    while (true)
    {
        asm volatile("cli; hlt");
    }
}

} // namespace nos::x86_64::interrupt
