#include <kernel/arch/x86_64/arch.hpp>

#include <log/log.hpp>

namespace NOS::X86_64 {

void Arch::initialize()
{
    Log::info(this).message("initialization");

    _gdt.load(_tss);
    _idt.load();

    _pic.initialize();
}

} // namespace NOS::X86_64
