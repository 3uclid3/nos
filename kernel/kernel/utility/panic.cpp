#include <kernel/utility/panic.hpp>

#include <kernel/arch/arch.hpp>
#include <kernel/utility/log.hpp>

namespace NOS {

void panic(StringView message, SourceLocation location)
{
    Log::newLine();

    Log::error(message);
    Log::error("File: {}", location.fileName());
    Log::error("Line: {}", location.line());
    Log::error("Column: {}", location.column());
    Log::error("Function: {}", location.functionName());
    Log::error("System halted");

    Arch::hcf();
}

} // namespace NOS
