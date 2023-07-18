#include <apidef.h>
#include NOS_LIBC_INCLUDE_STRING_H

#include <stdint.h>

void* NOS_LIBC(memmove)(void* destination, const void* source, size_t size)
{
    uint8_t* u8Destination = destination;
    const uint8_t* u8Source = (const uint8_t*)source;

    if (destination < source)
    {
        for(size_t i = 0; i < size; ++i)
        {
            u8Destination[i] = u8Source[i];
        }
    }
    else
    {
        for(size_t i = size; i--;)
        {
            u8Destination[i] = u8Source[i];
        }
    }

    return destination;
}
