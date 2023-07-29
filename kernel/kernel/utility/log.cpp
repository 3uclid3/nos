#include <kernel/utility/log.hpp>

#include <kernel/drivers/serial.hpp>

namespace NOS::Log {

namespace Details {

// Indentation is handled with ' ' to always have similar space on screen
constexpr size_t step = 2;

size_t currentIndent = 0;

} // namespace Details

void newLine()
{
    Serial::write(Serial::Ports[0], '\n');
}

void indent(size_t size)
{
    Details::currentIndent += size * Details::step;
}

void unindent(size_t size)
{
    NOS_ASSERT(size * Details::step <= Details::currentIndent);

    Details::currentIndent -= size * Details::step;
}

ScopeIndent::ScopeIndent(size_t s)
    : size(s)
{
    indent(size);
}

ScopeIndent::~ScopeIndent()
{
    unindent(size);
}

ScopeUnindent::ScopeUnindent(size_t s)
    : size(s)
{
    unindent(size);
}

ScopeUnindent::~ScopeUnindent()
{
    indent(size);
}

namespace Details {

struct SerialOutput
{
    static constexpr StringView Indent{"                                                  "};

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
        write(Indent.substr(0, currentIndent));
    }
};

void infoImpl(StringView fmt, Span<FormatArgument> arguments)
{
    SerialOutput output;
    output.write("[\033[36mINFO\033[0m] ");
    output.writeIndent();
    formatTo(output, fmt, arguments);
    output.write('\n');
}

void warnImpl(StringView fmt, Span<FormatArgument> arguments)
{
    SerialOutput output;
    output.write("[\033[33mWARN\033[0m] ");
    output.writeIndent();
    formatTo(output, fmt, arguments);
    output.write('\n');
}

void errorImpl(StringView fmt, Span<FormatArgument> arguments)
{
    SerialOutput output;
    output.write("[\033[31mERROR\033[0m] ");
    output.writeIndent();
    formatTo(output, fmt, arguments);
    output.write('\n');
}

} // namespace Details

} // namespace NOS::Log
