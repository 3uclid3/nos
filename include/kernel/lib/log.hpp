#pragma once

#include <format>
#include <string_view>

#include <lib/logging/level.hpp>
#include <lib/logging/logger.hpp>

namespace nos::log {

template<typename... ArgsT>
void trace(std::string_view fmt, const ArgsT&... args)
{
    logger::get().vlog(level::trace, fmt, std::make_format_args(args...));
}

template<typename... ArgsT>
void info(std::string_view fmt, const ArgsT&... args)
{
    logger::get().vlog(level::info, fmt, std::make_format_args(args...));
}

template<typename... ArgsT>
void warn(std::string_view fmt, const ArgsT&... args)
{
    logger::get().vlog(level::warn, fmt, std::make_format_args(args...));
}

template<typename... ArgsT>
void error(std::string_view fmt, const ArgsT&... args)
{
    logger::get().vlog(level::error, fmt, std::make_format_args(args...));
}

template<typename... ArgsT>
void fatal(std::string_view fmt, const ArgsT&... args)
{
    logger::get().vlog(level::fatal, fmt, std::make_format_args(args...));
}

template<typename SinkT, typename... ArgsT>
SinkT& add_sink(ArgsT&&... args)
{
    return logger::get().add_sink<SinkT>(std::forward<ArgsT>(args)...);
}

} // namespace nos::log
