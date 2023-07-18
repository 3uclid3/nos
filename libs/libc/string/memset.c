#include <string.h>

#include <stdint.h>

void* memset(void* ptr, int c, size_t size)
{
    const uint8_t value = (uint8_t)c; 

    uint8_t* it = (uint8_t*) ptr;
    const uint8_t* end = (uint8_t*)((size_t)ptr + size);

    for(; it != end; ++it)
    {
        *it = value;
    }

    return ptr;
}
