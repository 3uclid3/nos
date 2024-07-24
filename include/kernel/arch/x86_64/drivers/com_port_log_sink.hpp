#pragma once

#include <arch/x86_64/drivers/com_port.hpp>
#include <lib/logging/sink.hpp>

namespace nos::x86_64 {

class com_port_log_sink : public log::sink
{
public:
    void init(com_port port);

private:
    void log_impl(const log::message& message) override;

private:
    com_port _com;
};

} // namespace nos::x86_64
