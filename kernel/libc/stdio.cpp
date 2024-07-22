#include <stdio.h>

#include <stdlib.h>

extern "C" {

int fflush(FILE* stream)
{
    return 0;
}

void flockfile(FILE* stream)
{
}

void funlockfile(FILE* stream)
{
}

int fputc(char c, FILE* stream)
{
    return -1;
}

int fputs(const char* str, FILE* stream)
{
    return -1;
}

int fputws(const wchar_t* str, FILE* stream)
{
    return -1;
}

int fprintf(FILE* stream, const char* format, ...)
{
    return -1;
}

size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    return -1;
}

int vprintf(const char* format, va_list arg)
{
    return -1;
}

int printf(const char* format, ...)
{
    return -1;
}

int vsprintf(char* str, const char* format, va_list arg)
{
    return -1;
}

int sprintf(char* str, const char* format, ...)
{
    return -1;
}

int vsnprintf(char* str, size_t count, const char* format, va_list arg)
{
    return -1;
}

int snprintf(char* str, size_t count, const char* format, ...)
{
    return -1;
}

int vasprintf(char** str, const char* format, va_list arg)
{
    return -1;
}

int asprintf(char** str, const char* format, ...)
{
    return -1;
}
} // extern "C"