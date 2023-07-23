#include <utility/log.hpp>

#include <drivers/serial.hpp>

#include <arch/x86_64/io.hpp>

namespace NOS::Log {

constexpr Serial::Port Port = Serial::Port::COM1;

void printc(char c)
{
    Serial::write(Port, c);
}

void print(StringView msg)
{
    for (char c : msg)
    {
        Serial::write(Port, c);
    }
}

void printArgument(FormatArgument argument)
{
    Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '\n');

    switch (argument.getType())
    {
    case FormatArgument::Type::Bool:
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, 'B');
        NOS_ASSERT(false, "Unimplemented");
        break;
    case FormatArgument::Type::Char:
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, 'C');
        NOS_ASSERT(false, "Unimplemented");
        break;
    case FormatArgument::Type::SInt8:
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, 'S');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '8');
        NOS_ASSERT(false, "Unimplemented");
        break;
    case FormatArgument::Type::SInt16:
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, 'S');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '1');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '6');
        NOS_ASSERT(false, "Unimplemented");
        break;
    case FormatArgument::Type::SInt32:
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, 'S');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '3');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '2');
        NOS_ASSERT(false, "Unimplemented");
        break;
    case FormatArgument::Type::SInt64:
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, 'S');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '6');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '4');
        NOS_ASSERT(false, "Unimplemented");
        break;
    case FormatArgument::Type::UInt8:
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, 'U');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '8');
        NOS_ASSERT(false, "Unimplemented");
        break;
    case FormatArgument::Type::UInt16:
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, 'U');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '1');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '6');
        NOS_ASSERT(false, "Unimplemented");
        break;
    case FormatArgument::Type::UInt32:
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, 'U');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '3');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '2');
        NOS_ASSERT(false, "Unimplemented");
        break;
    case FormatArgument::Type::UInt64:
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, 'U');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '6');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, '4');
        NOS_ASSERT(false, "Unimplemented");
        break;
    case FormatArgument::Type::String:
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, 'S');
        Arch::IO::out<u8_t>(Arch::IO::Port::Debug, 'V');
        print(argument.asString());
        break;
    }
}

void vprintf(StringView fmt, Span<FormatArgument> arguments)
{
    size_t argIndex = 0;

    for (size_t i = 0; i < fmt.size(); ++i)
    {
        if (fmt[i] == '{' && i + 1 < fmt.size() && fmt[i + 1] == '}')
        {
            printArgument(arguments[argIndex++]);

            // skip }
            ++i;
        }
        else
        {
            Serial::write(Port, fmt[i]);
        }
    }
}

} // namespace NOS::Log
