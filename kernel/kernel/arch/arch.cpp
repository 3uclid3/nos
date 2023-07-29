#include <kernel/arch/arch.hpp>

#include <kernel/config.hpp>

#if NOS_ARCH_X86_64
#include <kernel/arch/x86_64/gdt.hpp>
#endif

namespace NOS::Arch {

void initialize()
{
#if NOS_ARCH_X86_64
    X86_64::GDT::initialize();
#endif
}

} // namespace NOS::Arch