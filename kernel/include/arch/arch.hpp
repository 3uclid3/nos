#pragma once

#include <string/string-view.hpp>

namespace nos::arch {

[[noreturn]] void hcf();

void print(StringView string);
void printc(char c);

} // namespace nos::arch
