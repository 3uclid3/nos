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
void log(Level level, Tag tag, StringView message, SourceLocation sourceLocation = SourceLocation::current());

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

struct LoggerProxy
{
    constexpr LoggerProxy(Level level_, Tag tag_, SourceLocation sourceLocation_)
        : sourceLocation(sourceLocation_)
        , level(level_)
        , tag(tag_)
    {
    }

    constexpr LoggerProxy& message(StringView message)
    {
        log(level, tag, message, sourceLocation);

        return *this;
    }

    template<typename... TArguments>
    constexpr LoggerProxy& format(StringView fmt, const TArguments&... rawArguments)
    {
        StaticArray arguments = makeFormatArguments(rawArguments...);
        vlog(level, tag, fmt, Span<FormatArgument>(arguments), sourceLocation);

        return *this;
    }

    SourceLocation sourceLocation;
    Level level;
    Tag tag;
};

template<Tagger TTagger>
LoggerProxy trace(SourceLocation sourceLocation = SourceLocation::current())
{
    return LoggerProxy(Level::Trace, TagOf<TTagger>, sourceLocation);
}

template<Tagger TTagger>
LoggerProxy trace(TTagger&&, SourceLocation sourceLocation = SourceLocation::current())
{
    return LoggerProxy(Level::Trace, TagOf<TTagger>, sourceLocation);
}

template<Tagger TTagger>
LoggerProxy debug(SourceLocation sourceLocation = SourceLocation::current())
{
    return LoggerProxy(Level::Debug, TagOf<TTagger>, sourceLocation);
}

template<Tagger TTagger>
LoggerProxy debug(TTagger&&, SourceLocation sourceLocation = SourceLocation::current())
{
    return LoggerProxy(Level::Debug, TagOf<TTagger>, sourceLocation);
}

template<Tagger TTagger>
LoggerProxy info(SourceLocation sourceLocation = SourceLocation::current())
{
    return LoggerProxy(Level::Info, TagOf<TTagger>, sourceLocation);
}

template<Tagger TTagger>
LoggerProxy info(TTagger&&, SourceLocation sourceLocation = SourceLocation::current())
{
    return LoggerProxy(Level::Info, TagOf<TTagger>, sourceLocation);
}

template<Tagger TTagger>
LoggerProxy warn(SourceLocation sourceLocation = SourceLocation::current())
{
    return LoggerProxy(Level::Warn, TagOf<TTagger>, sourceLocation);
}

template<Tagger TTagger>
LoggerProxy warn(TTagger&&, SourceLocation sourceLocation = SourceLocation::current())
{
    return LoggerProxy(Level::Warn, TagOf<TTagger>, sourceLocation);
}

template<Tagger TTagger>
LoggerProxy error(SourceLocation sourceLocation = SourceLocation::current())
{
    return LoggerProxy(Level::Error, TagOf<TTagger>, sourceLocation);
}

template<Tagger TTagger>
LoggerProxy error(TTagger&&, SourceLocation sourceLocation = SourceLocation::current())
{
    return LoggerProxy(Level::Error, TagOf<TTagger>, sourceLocation);
}

template<Tagger TTagger>
LoggerProxy fatal(SourceLocation sourceLocation = SourceLocation::current())
{
    return LoggerProxy(Level::Fatal, TagOf<TTagger>, sourceLocation);
}

template<Tagger TTagger>
LoggerProxy fatal(TTagger&&, SourceLocation sourceLocation = SourceLocation::current())
{
    return LoggerProxy(Level::Fatal, TagOf<TTagger>, sourceLocation);
}

} // namespace NOS::Log
