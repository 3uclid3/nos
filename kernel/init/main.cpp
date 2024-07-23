#include <cstdio>
#include <format>
#include <string_view>

#include <kdef.hpp>

#ifndef __cplusplus
#error "not c++"
#endif

extern "C" void _start()
{
    char buf[256];
    std::sprintf(buf, "Hello, %s!\n", "world");
    auto r = std::format("Hello, {}!\n", "world");

    while (true) asm volatile("cli; hlt");
}
