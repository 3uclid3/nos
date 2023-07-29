#pragma once

#include <ncxx/container/span.hpp>
#include <ncxx/container/static-array.hpp>
#include <ncxx/string/format-to.hpp>

namespace NOS::Log {

void newLine();

void indent(size_t size = 1);
void unindent(size_t size = 1);

template<typename... TArguments>
void info(StringView fmt, const TArguments&... rawArguments);

template<typename... TArguments>
void warn(StringView fmt, const TArguments&... rawArguments);

template<typename... TArguments>
void error(StringView fmt, const TArguments&... rawArguments);

struct ScopeIndent
{
    ScopeIndent(size_t s = 1);
    ~ScopeIndent();

    size_t size;
};

struct ScopeUnindent
{
    ScopeUnindent(size_t s = 1);
    ~ScopeUnindent();

    size_t size;
};

namespace Details {

void infoImpl(StringView fmt, Span<FormatArgument> arguments);
void warnImpl(StringView fmt, Span<FormatArgument> arguments);
void errorImpl(StringView fmt, Span<FormatArgument> arguments);

} // namespace Details

template<typename... TArguments>
void info(StringView fmt, const TArguments&... rawArguments)
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    Details::infoImpl(fmt, Span<FormatArgument>(arguments));
}

template<typename... TArguments>
void warn(StringView fmt, const TArguments&... rawArguments)
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    Details::warnImpl(fmt, Span<FormatArgument>(arguments));
}

template<typename... TArguments>
void error(StringView fmt, const TArguments&... rawArguments)
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    Details::errorImpl(fmt, Span<FormatArgument>(arguments));
}

} // namespace NOS::Log
