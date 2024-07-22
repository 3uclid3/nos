#include <stdio.h>

#include <printf/printf.h>
#include <stdlib.h>

HEDLEY_BEGIN_C_DECLS

void putchar_(char c)
{
    // TODO logging
}

int fflush(FILE* stream)
{
    return 0;
}

int fputc(char c, FILE* stream)
{
    // TODO impl fputc
    return c;
}

int fputs(const char* str, FILE* stream)
{
    // TODO impl fputs
    return -1;
}

int fputws(const wchar_t* str, FILE* stream)
{
    // TODO impl fputsw
    return -1;
}

int fprintf(FILE* stream, const char* format, ...)
{
    va_list arg;
    va_start(arg, format);

    int ret = vprintf(format, arg);

    va_end(arg);
    return ret;
}

size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    // TODO impl fwrite
    return -1;
}

int vprintf(const char* format, va_list arg)
{
    return vprintf_(format, arg);
}

int printf(const char* format, ...)
{
    va_list arg;
    va_start(arg, format);

    int ret = vprintf(format, arg);

    va_end(arg);
    return ret;
}

int vsprintf(char* str, const char* format, va_list arg)
{
    return vsprintf_(str, format, arg);
}

int sprintf(char* str, const char* format, ...)
{
    va_list arg;
    va_start(arg, format);

    int ret = vsprintf(str, format, arg);

    va_end(arg);
    return ret;
}

int vsnprintf(char* str, size_t count, const char* format, va_list arg)
{
    return vsnprintf_(str, count, format, arg);
}

int snprintf(char* str, size_t count, const char* format, ...)
{
    va_list arg;
    va_start(arg, format);

    int ret = vsnprintf(str, count, format, arg);

    va_end(arg);
    return ret;
}

int vasprintf(char** str, const char* format, va_list arg)
{
    va_list tmpa;
    va_copy(tmpa, arg);

    int ret = vsnprintf(NULL, 0, format, tmpa);

    va_end(tmpa);

    if (ret < 0)
        return -1;

    *str = static_cast<char*>(malloc(ret + 1));

    if (*str == nullptr)
        return -1;

    ret = vsprintf(*str, format, arg);
    return ret;
}

int asprintf(char** str, const char* format, ...)
{
    va_list arg;
    va_start(arg, format);

    int ret = vasprintf(str, format, arg);

    va_end(arg);
    return ret;
}

HEDLEY_END_C_DECLS
