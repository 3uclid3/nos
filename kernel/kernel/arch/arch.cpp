#include <kernel/arch/arch.hpp>

#include <kernel/cxx/cxxabi.hpp>

#include NOS_INCLUDE_KERNEL_ARCH(drivers/serial.hpp)

namespace nos {

void arch::early_init()
{
    current_arch::serial::early_init();
    cxxabi::init();
    super::early_init();
}

} // namespace nos