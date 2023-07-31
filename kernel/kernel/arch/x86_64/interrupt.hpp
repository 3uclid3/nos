#pragma once

#include <kernel/utility/log.hpp>
#include <ncxx/basic-types.hpp>
#include <ncxx/utility/source-location.hpp>

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

inline void enable(SourceLocation sourceLocation = SourceLocation::current())
{
    Log::info("Interrupt: enable from    {} ({}:{})", sourceLocation.fileName(), sourceLocation.line(), sourceLocation.column());
    asm volatile("sti");
}

inline void disable(SourceLocation sourceLocation = SourceLocation::current())
{
    Log::info("Interrupt: disable from    {} ({}:{})", sourceLocation.fileName(), sourceLocation.line(), sourceLocation.column());
    asm volatile("cli");
}

inline void halt(SourceLocation sourceLocation = SourceLocation::current())
{
    Log::info("Interrupt: halt from    {} ({}:{})", sourceLocation.fileName(), sourceLocation.line(), sourceLocation.column());
    asm volatile("hlt");
}

[[noreturn]] inline void hcf(SourceLocation sourceLocation = SourceLocation::current())
{
    Log::info("Interrupt: hcf from    {} ({}:{})", sourceLocation.fileName(), sourceLocation.line(), sourceLocation.column());
    while (true)
        asm volatile("cli; hlt");
}

} // namespace NOS::X86_64::Interrupt
