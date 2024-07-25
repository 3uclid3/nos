#pragma once

#include <format>
#include <string_view>

#include <kdef.hpp>

namespace nos {

std::string_view vformat_sv(std::string_view fmt, std::format_args args);

inline std::string_view format_sv(std::string_view fmt, auto... args)
{
    return format_sv(fmt, std::make_format_args(args...));
}

} // namespace nos
