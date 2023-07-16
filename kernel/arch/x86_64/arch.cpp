#include <arch/arch.hpp>

#include <arch/x86_64/io.hpp>

namespace nos::arch {

void hcf()
{
    while (true)
    {
        asm volatile("cli; hlt");
    }    
}

void print(string_view string)
{
    for (char c : string)
    {
        printc(c);
    }
}

void printc(char c)
{
    x86_64::io::out(x86_64::io::port::debug, static_cast<u8_t>(c));
}

} // namespace nos::arch
