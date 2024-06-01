#pragma once

#include <kernel/def.hpp>
#include <kernel/utility/details/main-logger.hpp>
#include <kernel/utility/log-level.hpp>
#include <nxx/container/span.hpp>
#include <nxx/string/format-argument.hpp>

namespace nos::log {

template<typename... ArgsT>
void trace(string_view fmt, const ArgsT&... raw_args)
{
    static_array args = make_format_arguments(raw_args...);
    details::main_logger::get().vlog(log_level::trace, fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void info(string_view fmt, const ArgsT&... raw_args)
{
    static_array args = make_format_arguments(raw_args...);
    details::main_logger::get().vlog(log_level::info, fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void warn(string_view fmt, const ArgsT&... raw_args)
{
    static_array args = make_format_arguments(raw_args...);
    details::main_logger::get().vlog(log_level::warn, fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void error(string_view fmt, const ArgsT&... raw_args)
{
    static_array args = make_format_arguments(raw_args...);
    details::main_logger::get().vlog(log_level::error, fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void fatal(string_view fmt, const ArgsT&... raw_args)
{
    static_array args = make_format_arguments(raw_args...);
    details::main_logger::get().vlog(log_level::fatal, fmt, span<format_argument>(args));
}

template<typename LoggerT, typename... ArgsT>
LoggerT& add_logger(ArgsT&&... args)
{
    return details::main_logger::get().add_logger<LoggerT>(forward<ArgsT>(args)...);
}

} // namespace nos::log
