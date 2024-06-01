#pragma once

#include <kernel/arch/x86_64/drivers/com-port.hpp>
#include <kernel/utility/logger.hpp>

namespace nos::x86_64 {

class com_port_logger : public logger
{
public:
    void init(com_port port);

private:
    void log_impl(string_view str) override;

private:
    com_port _com;
};

} // namespace nos::x86_64