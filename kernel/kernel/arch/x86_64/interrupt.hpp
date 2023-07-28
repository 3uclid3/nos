#pragma once

#include <ncxx/basic-types.hpp>

namespace NOS::X86_64::Interrupt {

inline bool isEnabled()
{
    u64_t flags;
    asm volatile(
        "pushfq\n"
        "\rpop %0"
        : "=r"(flags));

    return (flags & 0x200) != 0;
}

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
    while(true)
        asm volatile("cli; hlt");
}

} // namespace NOS::X86_64::Interrupt
