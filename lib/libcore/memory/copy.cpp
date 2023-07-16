#include <memory/copy.hpp>

#include <config.hpp>

namespace nos::memory {

void* copy(void* destination, const void* source, size_t size)
{
    byte* destinationBytes = reinterpret_cast<byte*>(destination);
    const byte* sourceBytes = reinterpret_cast<const byte*>(source);

    for (size_t i = 0; i < size; ++i)
    {
        destinationBytes[i] = sourceBytes[i];
    }

    return destination;
}

} // namespace nos::memory

#if NOS_ENABLE_LIBC_MEMORY

extern "C" void* memcpy(void* destination, const void* source, size_t size)
{
    return nos::memory::copy(destination, source, size);
}

#endif
