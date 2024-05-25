#pragma once

namespace nos::x86_64::serial {

void early_init();

char read();
void write(char c);

} // namespace nos::x86_64::serial
