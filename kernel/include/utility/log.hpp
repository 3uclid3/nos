#pragma once

#include <string/string-view.hpp>

namespace NOS::Log {

void printc(char c);
void print(StringView msg);

template<typename... TArgs>
void printf(StringView fmt, TArgs&&... args);

template<typename... TArgs>
void info(StringView fmt, TArgs&&... args);

template<typename... TArgs>
void warn(StringView fmt, TArgs&&... args);

template<typename... TArgs>
void error(StringView fmt, TArgs&&... args);

template<typename... TArgs>
void printf(StringView fmt, TArgs&&...)
{
    print(fmt);
}

template<typename... TArgs>
void info(StringView fmt, TArgs&&... args)
{
    print("[\033[36mINFO\033[0m] ");
    printf(fmt, args...);
    printc('\n');
}

template<typename... TArgs>
void warn(StringView fmt, TArgs&&... args)
{
    print("[\033[33mWARN\033[0m] ");
    printf(fmt, args...);
    printc('\n');
}

template<typename... TArgs>
void error(StringView fmt, TArgs&&... args)
{
    print("[\033[31mERROR\033[0m] ");
    printf(fmt, args...);
    printc('\n');
}

} // namespace NOS::Log
