#include <memory/move.hpp>

#include <config.hpp>

namespace nos::memory {
    
void* move(void* destination, const void* source, size_t size)
{
    byte* destinationBytes = static_cast<byte*>(destination);
    const byte* sourceBytes = static_cast<const byte*>(source);

    if (destination < source)
    {
        for (size_t i = 0; i < size; ++i)
        {
            destinationBytes[i] = sourceBytes[i];
        }
    }
    else
    {
        for (size_t i = size; i--;)
        {
            destinationBytes[i] = sourceBytes[i];
        }
    }

    return destination;
}

} // namespace nos::memory

#if NOS_ENABLE_LIBC_MEMORY

extern "C" void* memmove(void* destination, const void* source, size_t size)
{
    return nos::memory::move(destination, source, size);
}

#endif

