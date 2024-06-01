#pragma once

#include <kernel/def.hpp>
#include <kernel/log/level.hpp>
#include <kernel/log/logger.hpp>
#include <nxx/container/span.hpp>
#include <nxx/string/format_argument.hpp>

namespace nos::log {

template<typename... ArgsT>
void trace(string_view fmt, const ArgsT&... raw_args)
{
    static_array args = make_format_arguments(raw_args...);
    logger::get().vlog(level::trace, fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void info(string_view fmt, const ArgsT&... raw_args)
{
    static_array args = make_format_arguments(raw_args...);
    logger::get().vlog(level::info, fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void warn(string_view fmt, const ArgsT&... raw_args)
{
    static_array args = make_format_arguments(raw_args...);
    logger::get().vlog(level::warn, fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void error(string_view fmt, const ArgsT&... raw_args)
{
    static_array args = make_format_arguments(raw_args...);
    logger::get().vlog(level::error, fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void fatal(string_view fmt, const ArgsT&... raw_args)
{
    static_array args = make_format_arguments(raw_args...);
    logger::get().vlog(level::fatal, fmt, span<format_argument>(args));
}

template<typename SinkT, typename... ArgsT>
SinkT& add_sink(ArgsT&&... args)
{
    return logger::get().add_sink<SinkT>(forward<ArgsT>(args)...);
}

} // namespace nos::log
