#include <arch/arch.hpp>

#include <arch/x86_64/io.hpp>

namespace NOS::Arch {

void hcf()
{
    while (true)
    {
        asm volatile("cli; hlt");
    }
}

void print(StringView string)
{
    for (char c : string)
    {
        printc(c);
    }
}

void printc(char c)
{
    x86_64::IO::out(x86_64::IO::Port::Debug, static_cast<u8_t>(c));
}

} // namespace NOS::Arch
