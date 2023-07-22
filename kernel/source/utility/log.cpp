#include <utility/log.hpp>

#include <drivers/serial.hpp>

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

} // namespace NOS::Log
