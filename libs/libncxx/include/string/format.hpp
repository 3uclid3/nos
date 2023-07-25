#pragma once

#include <base-types.hpp>
#include <container/span.hpp>
#include <string/format-argument.hpp>
#include <string/string-view.hpp>

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
