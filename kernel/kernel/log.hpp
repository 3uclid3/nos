#pragma once

#include <kernel/def.hpp>
#include <nxx/string/format-to.hpp>

namespace nos::log {

void prints(string_view str);
void printc(char c);

void print(string_view fmt);
void println(string_view fmt);

void trace();
void traceln();

void info();
void infoln();

void warn();
void warnln();

void error();
void errorln();

void fatal();
void fatalln();

} // namespace nos::log
