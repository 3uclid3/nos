#pragma once

#include <kernel/arch/x86_64/drivers/com-port.hpp>
#include <kernel/utility/log.hpp>

namespace nos::x86_64 {

class com_log_printer : public log::printer
{
public:
    void init(com_port port);
    
private:
    void prints_impl(string_view str) override;
    void printc_impl(char c) override;

private:
    com_port _com;
};

} // namespace nos::x86_64
