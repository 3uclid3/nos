#pragma once

namespace nos::x86_64::arch {

void init();

[[noreturn]] void halt(bool ints = true);

void pause();

void shutdown(bool now);
void reboot(bool now);

} // namespace nos::x86_64::arch