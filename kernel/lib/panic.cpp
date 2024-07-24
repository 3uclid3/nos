#include <lib/panic.hpp>

#include <arch/arch.hpp>
#include <lib/log.hpp>

namespace nos {

void log_location(std::string_view file, int line, std::string_view func)
{
    log::fatal("File: {}", file);
    log::fatal("Line: {}", line);
    log::fatal("Function: {}", func);
}

void log_location(std::source_location location)
{
    log::fatal("File: {}", location.file_name());
    log::fatal("Line: {}", location.line());
    log::fatal("Column: {}", location.column());
    log::fatal("Function: {}", location.function_name());
}

void panic(std::string_view fmt, std::string_view file, int line, std::string_view func)
{
    log::vlog(log::level::fatal, fmt, {});
    log_location(file, line, func);

    // TODO backtrace
    // TODO stack dump

    log::fatal("nos: halting");
    arch::hcf();
}

void panic(std::string_view fmt, std::format_args args, std::source_location location)
{
    log::vlog(log::level::fatal, fmt, args);
    log_location(location);

    // TODO backtrace
    // TODO stack dump

    log::fatal("nos: halting");
    arch::hcf();
}

} // namespace nos
