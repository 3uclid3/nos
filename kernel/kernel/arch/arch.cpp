#include <kernel/arch/arch.hpp>

#include <kernel/config.hpp>

#include <kernel/utility/log.hpp>

#if NOS_ARCH_X86_64
#include <kernel/arch/x86_64/gdt.hpp>
#include <kernel/arch/x86_64/idt.hpp>
#endif

namespace NOS::Arch {

void initialize()
{
    Log::info("arch: initialization");
    Log::ScopeIndent indent{1};

#if NOS_ARCH_X86_64
    X86_64::GDT::initialize();
    X86_64::IDT::initialize();
#endif
}

} // namespace NOS::Arch