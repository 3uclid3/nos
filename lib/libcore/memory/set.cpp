#include <memory/set.hpp>

#include <config.hpp>

namespace nos::memory {

void* set(void* destination, u8_t value, size_t size)
{
    u8_t* it = static_cast<u8_t*>(destination);
    const u8_t* end = it + size;

    for (; it != end; ++it)
    {
        *it = value;
    }

    return destination;
}

} // namespace nos::memory

#if NOS_ENABLE_LIBC_MEMORY

extern "C" void* memset(void* destination, int value, size_t size)
{
    return nos::memory::set(destination, static_cast<nos::u8_t>(value), size);
}

#endif


