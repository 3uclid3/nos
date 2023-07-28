#include <kernel/utility/log.hpp>

#include <kernel/drivers/serial.hpp>

namespace NOS::Log {

void newLine()
{
    Serial::write(Serial::Ports[0], '\n');
}

namespace Details {

struct SerialOutput
{
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
};

void infoImpl(StringView fmt, Span<FormatArgument> arguments)
{
    SerialOutput output;
    output.write("[\033[36mINFO\033[0m] ");
    formatTo(output, fmt, arguments);
    output.write('\n');
}

void warnImpl(StringView fmt, Span<FormatArgument> arguments)
{
    SerialOutput output;
    output.write("[\033[33mWARN\033[0m] ");
    formatTo(output, fmt, arguments);
    output.write('\n');
}

void errorImpl(StringView fmt, Span<FormatArgument> arguments)
{
    SerialOutput output;
    output.write("[\033[31mERROR\033[0m] ");
    formatTo(output, fmt, arguments);
    output.write('\n');
}

} // namespace Details
} // namespace NOS::Log
