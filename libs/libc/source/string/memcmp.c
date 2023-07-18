#include <apidef.h>
#include NOS_LIBC_INCLUDE_STRING_H

#include <stdint.h>

int NOS_LIBC(memcmp)(const void* lhs, const void* rhs, size_t size)
{
    const uint8_t* u8lhs = (const uint8_t*)lhs;
    const uint8_t* u8rhs = (const uint8_t*)rhs;
    for (size_t i = 0; i < size; ++i)
    {
        if (u8lhs[i] < u8rhs[i])
        {
            return -1;
        }

        if (u8lhs[i] > u8rhs[i])
        {
            return 1;
        }
    }
    return 0;
}
