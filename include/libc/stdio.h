
#pragma once

#include <hedley.h>
#include <stdarg.h>
#include <stddef.h>

#define EOF (-1)

HEDLEY_BEGIN_C_DECLS

int printf(const char* format, ...) HEDLEY_PRINTF_FORMAT(1, 2);
int vprintf(const char* format, va_list arg) HEDLEY_PRINTF_FORMAT(1, 0);

int sprintf(char* str, const char* format, ...) HEDLEY_PRINTF_FORMAT(2, 3);
int vsprintf(char* str, const char* format, va_list arg) HEDLEY_PRINTF_FORMAT(2, 0);

int snprintf(char* str, size_t count, const char* format, ...) HEDLEY_PRINTF_FORMAT(3, 4);
int vsnprintf(char* str, size_t count, const char* format, va_list arg) HEDLEY_PRINTF_FORMAT(3, 0);

int vasprintf(char** str, const char* format, va_list arg) HEDLEY_PRINTF_FORMAT(2, 0);
int asprintf(char** str, const char* format, ...) HEDLEY_PRINTF_FORMAT(2, 3);

int fctprintf(void (*out)(char c, void* extra_arg), void* extra_arg, const char* format, ...);
int vfctprintf(void (*out)(char c, void* extra_arg), void* extra_arg, const char* format, va_list arg);

HEDLEY_END_C_DECLS
