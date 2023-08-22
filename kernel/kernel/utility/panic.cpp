#include <kernel/utility/panic.hpp>

#include <kernel/arch/interrupt.hpp>
#include <kernel/arch/x86_64/cpu.hpp>
#include <log/log.hpp>

namespace NOS {

void panic(StringView message, SourceLocation location)
{
    struct Panic
    {};
    // Log::newLine();

    if (!message.isEmpty())
    {
        Log::error<Panic>().message(message);
    }

    Log::error<Panic>().format("File: {}", location.fileName());
    Log::error<Panic>().format("Line: {}", location.line());
    Log::error<Panic>().format("Column: {}", location.column());
    Log::error<Panic>().format("Function: {}", location.functionName());
    Log::error<Panic>().message("System halted");

    Interrupt::hcf();
}

} // namespace NOS
