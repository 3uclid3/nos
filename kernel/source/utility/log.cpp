#include <utility/log.hpp>

#include <base-types.hpp>
#include <drivers/serial.hpp>
#include <string/format-to.hpp>

namespace NOS::Log::Details {

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
        Serial::write(Serial::Port::COM1, c);
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

} // namespace NOS::Log::Details
