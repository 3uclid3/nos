#include <kernel/arch/x86_64/drivers/com-port-log-printer.hpp>

namespace nos::x86_64 {

void com_port_log_printer::init(com_port com)
{
    _com = com;
    _com.init();

    NOS_ASSERT(_com.loopback_test());
}

void com_port_log_printer::prints_impl(string_view str)
{
    for (char c : str)
    {
        _com.write(c);
    }
}

void com_port_log_printer::printc_impl(char c)
{
    _com.write(c);
}

} // namespace nos::x86_64
