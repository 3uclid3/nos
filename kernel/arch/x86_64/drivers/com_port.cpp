#include <arch/x86_64/drivers/com_port.hpp>

namespace nos::x86_64 {

char com_port::read()
{
    return static_cast<char>(serial_port::read());
}

void com_port::write(char c)
{
    serial_port::write(static_cast<std::uint8_t>(c));
}

} // namespace nos::x86_64
