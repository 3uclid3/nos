#include <log/log.hpp>

#include <log/message.hpp>
#include <log/sink.hpp>
#include <ncxx/container/array.hpp>
#include <ncxx/memory/unique-ptr.hpp>
#include <ncxx/string/format.hpp>
#include <ncxx/utility/move.hpp>

namespace NOS::Log {

namespace Details { namespace {

struct Logger
{
    Array<UniquePtr<Sink>> sinks;
    Array<Tag> tags;
    Array<Level> tagsLevel;
    Level level{Level::Info};
};

Logger logger;

}} // namespace Details

void addSink(UniquePtr<Sink>&& sink)
{
    Details::logger.sinks.emplaceLast(move(sink));
}

void clearSinks()
{
    Details::logger.sinks.clear();
}

Level getLevel()
{
    return Details::logger.level;
}

void setLevel(Level level)
{
    Details::logger.level = level;
}

Level getLevel(Tag tag)
{
    const size_t index = Details::logger.tags.indexOf(tag);
    return index < Details::logger.tagsLevel.size() ? Details::logger.tagsLevel[index] : Level::Unset;
}

void setLevel(Tag tag, Level level)
{
    const size_t index = Details::logger.tags.indexOf(tag);

    if (index < Details::logger.tags.size())
    {
        Details::logger.tagsLevel[index] = level;
    }
    else
    {
        Details::logger.tags.append(tag);
        Details::logger.tagsLevel.append(level);
    }
}

void vlog(Level level, Tag tag, StringView fmt, Span<FormatArgument> args, SourceLocation sourceLocation)
{
    if (Details::logger.level == Level::Disable || level < Details::logger.level)
    {
        return;
    }

    const size_t index = Details::logger.tags.indexOf(tag);

    if (index < Details::logger.tags.size() && level < Details::logger.tagsLevel[index])
    {
        return;
    }

    const Message message{
        .sourceLocation = sourceLocation,
        .message = vformat(fmt, args),
        .tag = tag,
        .level = level};

    for (auto&& sink : Details::logger.sinks)
    {
        sink->log(message);
    }
}

} // namespace NOS::Log