#pragma once

#include <ncxx/string/string-view.hpp>

namespace NOS::Arch {

[[noreturn]] void hcf();
[[noreturn]] void halt();

void pause();

} // namespace NOS::Arch
