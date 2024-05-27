#pragma once

#include <kernel/def.hpp>
#include <nxx/container/span.hpp>
#include <nxx/string/format-to.hpp>
#include <nxx/string/string-view.hpp>
#include <nxx/type-trait/underlying-type.hpp>
#include <nxx/utility/source-location.hpp>

namespace nos::log {

enum class output : u8_t
{
    none = 0x0,
    serial = 0x1,
    terminal = 0x2,
    all = 0xF
};

constexpr output operator|(output lhs, output rhs)
{
    return static_cast<output>(static_cast<underlying_type<output>>(lhs) | static_cast<underlying_type<output>>(rhs));
}

constexpr output operator&(output lhs, output rhs)
{
    return static_cast<output>(static_cast<underlying_type<output>>(lhs) & static_cast<underlying_type<output>>(rhs));
}

void set_output(output out);

void prints(string_view str);
void printc(char c);

void vprint(string_view fmt, span<format_argument> args);

template<typename... ArgsT>
void print(string_view fmt, const ArgsT&... raw_args)
{
    static_array arguments = make_format_arguments(raw_args...);
    vprint(fmt, span<format_argument>(arguments));
}

template<typename... ArgsT>
void println(string_view fmt = {}, const ArgsT&... raw_args)
{
    if (!fmt.is_empty())
    {
        static_array arguments = make_format_arguments(raw_args...);
        vprint(fmt, span<format_argument>(arguments));
    }
    printc('\n');
}

constexpr auto trace_level = "[\033[31mTRACE\033[0m] ";
constexpr auto info_level = "[\033[36mINFO\033[0m] ";
constexpr auto warn_level = "[\033[33mWARN\033[0m] ";
constexpr auto error_level = "[\033[31mERROR\033[0m] ";
constexpr auto fatal_level = "[\033[31mFATAL\033[0m] ";

template<typename... ArgsT>
void trace(string_view fmt, const ArgsT&... raw_args)
{
    prints(trace_level);
    static_array args = make_format_arguments(raw_args...);
    vprint(fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void traceln(string_view fmt, const ArgsT&... raw_args)
{
    prints(trace_level);
    static_array args = make_format_arguments(raw_args...);
    vprint(fmt, span<format_argument>(args));
    printc('\n');
}

template<typename... ArgsT>
void info(string_view fmt, const ArgsT&... raw_args)
{
    prints(info_level);
    static_array args = make_format_arguments(raw_args...);
    vprint(fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void infoln(string_view fmt, const ArgsT&... raw_args)
{
    prints(info_level);
    static_array args = make_format_arguments(raw_args...);
    vprint(fmt, span<format_argument>(args));
    printc('\n');
}

template<typename... ArgsT>
void warn(string_view fmt, const ArgsT&... raw_args)
{
    prints(warn_level);
    static_array args = make_format_arguments(raw_args...);
    vprint(fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void warnln(string_view fmt, const ArgsT&... raw_args)
{
    prints(warn_level);
    static_array args = make_format_arguments(raw_args...);
    vprint(fmt, span<format_argument>(args));
    printc('\n');
}

template<typename... ArgsT>
void error(string_view fmt, const ArgsT&... raw_args)
{
    prints(error_level);
    static_array args = make_format_arguments(raw_args...);
    vprint(fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void errorln(string_view fmt, const ArgsT&... raw_args)
{
    prints(error_level);
    static_array args = make_format_arguments(raw_args...);
    vprint(fmt, span<format_argument>(args));
    printc('\n');
}

template<typename... ArgsT>
void fatal(string_view fmt, const ArgsT&... raw_args)
{
    prints(fatal_level);
    static_array args = make_format_arguments(raw_args...);
    vprint(fmt, span<format_argument>(args));
}

template<typename... ArgsT>
void fatalln(string_view fmt, const ArgsT&... raw_args)
{
    prints(fatal_level);
    static_array args = make_format_arguments(raw_args...);
    vprint(fmt, span<format_argument>(args));
    printc('\n');
}

} // namespace nos::log
