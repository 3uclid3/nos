#include <utility/panic.hpp>

#include <arch/arch.hpp>
#include <utility/log.hpp>

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
