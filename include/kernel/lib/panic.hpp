#pragma once

#include <format>
#include <source_location>
#include <string_view>

#include <kdef.hpp>

namespace nos {

HEDLEY_NO_RETURN void panic(std::string_view msg, std::string_view file, int line, std::string_view func);
HEDLEY_NO_RETURN void panic(std::string_view fmt, std::format_args args, std::source_location location = std::source_location::current());
HEDLEY_NO_RETURN void panic(std::string_view fmt, auto... args, std::source_location location = std::source_location::current())
{
    panic(fmt, std::format_args(args...), location);
}

} // namespace nos
