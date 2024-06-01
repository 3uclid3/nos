#include <kernel/arch/x86_64/drivers/com-port-logger.hpp>

namespace nos::x86_64 {

void com_port_logger::init(com_port com)
{
    _com = com;
    _com.init();

    NOS_ASSERT(_com.loopback_test());
}

void com_port_logger::log_impl(string_view str)
{
    for (char c : str)
    {
        _com.write(c);
    }
    _com.write('\n');
}

} // namespace nos::x86_64
