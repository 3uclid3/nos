#include <stdlib.h>

BEGIN_C_DECLS

void* malloc(size_t size)
{
    return 0;
}

void* calloc(size_t num, size_t size)
{
    return 0;
}

void* realloc(void* oldptr, size_t size)
{
    return 0;
}

void free(void* ptr)
{
}

size_t allocsize(void* ptr)
{
    return 0;
}

int atoi(const char* str)
{
    return 0;
}

long atol(const char* str)
{
    return 0;
}

long long atoll(const char* str)
{
    return 0;
}

long strtol(const char* str, char** str_end, int base)
{
    return 0;
}

long long strtoll(const char* str, char** str_end, int base)
{
    return 0;
}

unsigned long strtoul(const char* str, char** str_end, int base)
{
    return 0;
}

unsigned long long strtoull(const char* str, char** str_end, int base)
{
    return 0;
}

END_C_DECLS
