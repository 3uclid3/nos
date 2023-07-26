#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/container/span.hpp>
#include <ncxx/string/format-argument.hpp>
#include <ncxx/string/string-view.hpp>

namespace NOS {

template<typename... TArguments>
StringView format(StringView fmt, const TArguments&... rawArguments);
StringView vformat(StringView fmt, Span<FormatArgument> arguments);

template<typename... TArguments>
StringView format(StringView fmt, const TArguments&... rawArguments)
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    return vformat(fmt, arguments);
}

} // namespace NOS
