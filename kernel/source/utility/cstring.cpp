#include <stddef.h>

// LLVM tries to call them (e.g. memset when ctor an empy StringView)
extern "C" {
int memcmp(const void* str1, const void* str2, size_t n)
{
    return __builtin_memcmp(str1, str2, n);
}

void* memcpy(void* dest, const void* src, size_t n)
{
    return __builtin_memcpy(dest, src, n);
}

void* memmove(void* dest, const void* src, size_t n)
{
    return __builtin_memmove(dest, src, n);
}

void* memset(void* str, int c, size_t n)
{
    return __builtin_memset(str, c, n);
}
}
