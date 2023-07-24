#pragma once

#include <container/span.hpp>
#include <container/static-array.hpp>
#include <string/format-to.hpp>

namespace NOS::Log {

template<typename... TArguments>
void info(StringView fmt, const TArguments&... rawArguments);

template<typename... TArguments>
void warn(StringView fmt, const TArguments&... rawArguments);

template<typename... TArguments>
void error(StringView fmt, const TArguments&... rawArguments);

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
