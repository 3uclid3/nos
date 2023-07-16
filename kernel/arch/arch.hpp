#pragma once

#include <string/string_view.hpp>

namespace nos::arch {

[[noreturn]] void hcf();

void print(string_view string);
void printc(char c);

} // namespace nos::arch
