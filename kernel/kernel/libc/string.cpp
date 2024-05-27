#include <string.hpp>

#include <kernel/def.hpp>

extern "C" {

int memcmp(const void* ptr1, const void* ptr2, size_t len)
{
    auto p1 = static_cast<const nos::u8_t*>(ptr1);
    auto p2 = static_cast<const nos::u8_t*>(ptr2);

    for (size_t i = 0; i < len; ++i)
    {
        if (p1[i] != p2[i])
        {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }
    return 0;
}

void* memcpy(void* dest, const void* src, size_t len)
{
    auto pdest = static_cast<nos::u8_t*>(dest);
    auto psrc = static_cast<const nos::u8_t*>(src);

    for (size_t i = 0; i < len; ++i)
    {
        pdest[i] = psrc[i];
    }

    return dest;
}

void* memset(void* ptr, int ch, size_t len)
{
    auto p = static_cast<nos::u8_t*>(ptr);

    for (size_t i = 0; i < len; ++i)
    {
        p[i] = static_cast<nos::u8_t>(ch);
    }

    return ptr;
}

void* memmove(void* dest, const void* src, size_t len)
{
    auto pdest = static_cast<nos::u8_t*>(dest);
    auto psrc = static_cast<const nos::u8_t*>(src);

    if (src > dest)
    {
        for (size_t i = 0; i < len; ++i)
        {
            pdest[i] = psrc[i];
        }
    }
    else if (src < dest)
    {
        for (size_t i = len; i > 0; --i)
        {
            pdest[i - 1] = psrc[i - 1];
        }
    }
    return dest;
}

size_t strlen(const char* str)
{
    size_t length = 0;
    while (str[length]) { length++; }
    return length;
}

char* strcpy(char* dest, const char* src)
{
    char* ptr = dest;
    while (*src != '\0')
    {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = '\0';
    return ptr;
}

char* strncpy(char* dest, const char* src, size_t len)
{
    char* ptr = dest;
    while (*src != '\0' && len--)
    {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = '\0';
    return ptr;
}

int strcmp(const char* str1, const char* str2)
{
    while (*str1 && *str2 && *str1 == *str2)
    {
        ++str1;
        ++str2;
    }
    return *str1 - *str2;
}

int strncmp(const char* str1, const char* str2, size_t len)
{
    while (*str1 && *str2 && *str1 == *str2 && len--)
    {
        ++str1;
        ++str2;
    }

    if (len == 0)
    {
        return 0;
    }

    return *str1 - *str2;
}

} // extern C
