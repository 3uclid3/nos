#include <kernel/arch/x86_64/arch.hpp>

#include <kernel/utility/log.hpp>

namespace NOS::X86_64 {

void Arch::initialize()
{
    Log::info("arch: initialization");
    Log::ScopeIndent indent{1};

    _gdt.load(_tss);
    _idt.load();
}

} // namespace NOS::X86_64
