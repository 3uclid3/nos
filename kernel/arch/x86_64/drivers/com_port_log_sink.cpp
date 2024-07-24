#include <arch/x86_64/drivers/com_port_log_sink.hpp>

#include <cassert>

#include <log/message.hpp>

namespace nos::x86_64 {

void com_port_log_sink::init(com_port com)
{
    _com = com;
    _com.init();

    assert(_com.loopback_test());
}

void com_port_log_sink::log_impl(const log::message& message)
{
    for (char c : message.string)
    {
        _com.write(c);
    }

    _com.write('\n');
}

} // namespace nos::x86_64
