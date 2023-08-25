#include <kernel/log/serial-sink.hpp>

#include <kernel/drivers/serial.hpp>
#include <log/level.hpp>
#include <log/message.hpp>
#include <ncxx/string/format-to.hpp>

namespace NOS::Log {

namespace {

struct SerialOutput
{
    // static constexpr StringView Indent{"                                                  "};

    void write(StringView str)
    {
        for (char c : str)
        {
            write(c);
        }
    }

    void write(char c)
    {
        Serial::write(Serial::Ports[0], c);
    }

    void writeIndent()
    {
        // write(Indent.substr(0, currentIndent));
    }
};

int getColor(Level level)
{
    switch (level)
    {
    case Level::Trace:
        return 31;
    case Level::Debug:
        return 31;
    case Level::Info:
        return 36;
    case Level::Warn:
        return 33;
    case Level::Error:
        return 31;
    case Level::Fatal:
        return 31;

    case Level::Disable:
    case Level::Unset:
    case Level::Count:
        NOS_ASSERT(false);
        return 0;
    }
}

} // namespace

void SerialSink::logImpl(const Message& message)
{
    // color - level - tag - msg
    constexpr StringView fmt = "[\033[{}m{}\033[0m] {}: {}";

    SerialOutput output;
    formatTo(output, fmt, getColor(message.level), LevelString.string(message.level), message.tag.name, message.message);
    output.write('\n');
}

} // namespace NOS::Log