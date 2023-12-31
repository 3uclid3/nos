#pragma once

#include <log/log.hpp>
#include <ncxx/basic-types.hpp>
#include <ncxx/utility/source-location.hpp>

namespace NOS::X86_64::Interrupt {

bool isEnabled();

void enable(SourceLocation sourceLocation = SourceLocation::current());
void disable(SourceLocation sourceLocation = SourceLocation::current());

void halt(SourceLocation sourceLocation = SourceLocation::current());

[[noreturn]] void hcf(SourceLocation sourceLocation = SourceLocation::current());

// logging tag
struct Interrupt
{};

inline bool isEnabled()
{
    u64_t flags;
    asm volatile(
        "pushfq\n"
        "\rpop %0"
        : "=r"(flags));

    return (flags & 0x200) != 0;
}

inline void enable(SourceLocation sourceLocation)
{
    Log::trace<Interrupt>().format("enable from    {} ({}:{})", sourceLocation.fileName(), sourceLocation.line(), sourceLocation.column());
    asm volatile("sti");
}

inline void disable(SourceLocation sourceLocation)
{
    Log::trace<Interrupt>().format("disable from    {} ({}:{})", sourceLocation.fileName(), sourceLocation.line(), sourceLocation.column());
    asm volatile("cli");
}

inline void halt(SourceLocation sourceLocation)
{
    Log::trace<Interrupt>().format("halt from    {} ({}:{})", sourceLocation.fileName(), sourceLocation.line(), sourceLocation.column());
    asm volatile("hlt");
}

[[noreturn]] inline void hcf(SourceLocation sourceLocation)
{
    Log::trace<Interrupt>().format("hcf from    {} ({}:{})", sourceLocation.fileName(), sourceLocation.line(), sourceLocation.column());
    while (true)
    {
        asm volatile("cli; hlt");
    }
}

} // namespace NOS::X86_64::Interrupt
