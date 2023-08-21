#pragma once

#include <log/level.hpp>
#include <log/tag.hpp>
#include <ncxx/container/span.hpp>
#include <ncxx/memory/unique-ptr.hpp>
#include <ncxx/string/format-argument.hpp>
#include <ncxx/string/string-view.hpp>
#include <ncxx/type-trait/decay.hpp>
#include <ncxx/utility/forward.hpp>
#include <ncxx/utility/source-location.hpp>

namespace NOS::Log {

class Sink;

struct Message;

void addSink(UniquePtr<Sink>&& sink);
void clearSinks();

Level getLevel();
void setLevel(Level level);

Level getLevel(Tag tag);
void setLevel(Tag tag, Level level);

template<Tagger TTagger>
Level getLevel();

template<Tagger TTagger>
void setLevel(Level level);

void vlog(Level level, Tag tag, StringView fmt, Span<FormatArgument> args, SourceLocation sourceLocation = SourceLocation::current());

template<Tagger TTagger>
Level getLevel()
{
    return getLevel(TagOf<TTagger>);
}

template<Tagger TTagger>
void setLevel(Level level)
{
    setLevel(TagOf<TTagger>, level);
}

template<Tagger TTagger, typename... TArguments>
void trace(StringView fmt, const TArguments&... rawArguments, SourceLocation sourceLocation = SourceLocation::current())
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    vlog(Level::Trace, TagOf<TTagger>, fmt, Span<FormatArgument>(arguments), sourceLocation);
}

template<Tagger TTagger, typename... TArguments>
void trace(TTagger&&, StringView fmt, const TArguments&... rawArguments, SourceLocation sourceLocation = SourceLocation::current())
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    vlog(Level::Trace, TagOf<DecayT<TTagger>>, fmt, Span<FormatArgument>(arguments), sourceLocation);
}

template<Tagger TTagger, typename... TArguments>
void debug(StringView fmt, const TArguments&... rawArguments, SourceLocation sourceLocation = SourceLocation::current())
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    vlog(Level::Debug, TagOf<TTagger>, fmt, Span<FormatArgument>(arguments), sourceLocation);
}

template<Tagger TTagger, typename... TArguments>
void debug(TTagger&&, StringView fmt, const TArguments&... rawArguments, SourceLocation sourceLocation = SourceLocation::current())
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    vlog(Level::Debug, TagOf<TTagger>, fmt, Span<FormatArgument>(arguments), sourceLocation);
}

template<Tagger TTagger, typename... TArguments>
void info(StringView fmt, const TArguments&... rawArguments, SourceLocation sourceLocation = SourceLocation::current())
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    vlog(Level::Info, TagOf<TTagger>, fmt, Span<FormatArgument>(arguments), sourceLocation);
}

template<Tagger TTagger, typename... TArguments>
void info(TTagger&&, StringView fmt, const TArguments&... rawArguments, SourceLocation sourceLocation = SourceLocation::current())
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    vlog(Level::Info, TagOf<TTagger>, fmt, Span<FormatArgument>(arguments), sourceLocation);
}

template<Tagger TTagger, typename... TArguments>
void warn(StringView fmt, const TArguments&... rawArguments, SourceLocation sourceLocation = SourceLocation::current())
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    vlog(Level::Warn, TagOf<TTagger>, fmt, Span<FormatArgument>(arguments), sourceLocation);
}

template<Tagger TTagger, typename... TArguments>
void warn(TTagger&&, StringView fmt, const TArguments&... rawArguments, SourceLocation sourceLocation = SourceLocation::current())
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    vlog(Level::Warn, TagOf<TTagger>, fmt, Span<FormatArgument>(arguments), sourceLocation);
}

template<Tagger TTagger, typename... TArguments>
void error(StringView fmt, const TArguments&... rawArguments, SourceLocation sourceLocation = SourceLocation::current())
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    vlog(Level::Error, TagOf<TTagger>, fmt, Span<FormatArgument>(arguments), sourceLocation);
}

template<Tagger TTagger, typename... TArguments>
void error(TTagger&&, StringView fmt, const TArguments&... rawArguments, SourceLocation sourceLocation = SourceLocation::current())
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    vlog(Level::Error, TagOf<TTagger>, fmt, Span<FormatArgument>(arguments), sourceLocation);
}

template<Tagger TTagger, typename... TArguments>
void fatal(StringView fmt, const TArguments&... rawArguments, SourceLocation sourceLocation = SourceLocation::current())
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    vlog(Level::Fatal, TagOf<TTagger>, fmt, Span<FormatArgument>(arguments), sourceLocation);
}

template<Tagger TTagger, typename... TArguments>
void fatal(TTagger&&, StringView fmt, const TArguments&... rawArguments, SourceLocation sourceLocation = SourceLocation::current())
{
    StaticArray arguments = makeFormatArguments(rawArguments...);
    vlog(Level::Fatal, TagOf<TTagger>, fmt, Span<FormatArgument>(arguments), sourceLocation);
}

} // namespace NOS::Log
