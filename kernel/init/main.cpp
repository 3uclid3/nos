#include <string_view>

extern "C" void _start()
{
    std::string_view sv = "hello";

    while (!sv.empty())
        asm volatile ("cli; hlt");
}
