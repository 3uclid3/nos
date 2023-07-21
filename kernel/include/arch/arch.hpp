#pragma once

#include <string/string-view.hpp>

namespace NOS::Arch {

[[noreturn]] void hcf();

void print(StringView string);
void printc(char c);

} // namespace NOS::Arch
