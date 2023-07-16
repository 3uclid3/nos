#include <memory/compare.hpp>

#include <config.hpp>

namespace nos::memory {
    
compare_result compare(const void* lhs, const void* rhs, size_t size)
{
    const uint8_t* lhsBytes = static_cast<const uint8_t*>(lhs);
    const uint8_t* rhsBytes = static_cast<const uint8_t*>(rhs);
    for (size_t i = 0; i < size; ++i)
    {
        if (lhsBytes[i] < rhsBytes[i])
        {
            return compare_result::lesser;
        }
        
        if (lhsBytes[i] > rhsBytes[i])
        {
            return compare_result::greater;
        }
    }

    return compare_result::equals;
}

} // namespace nos::memory

#if NOS_ENABLE_LIBC_MEMORY

extern "C" int memcmp(void* destination, const void* source, size_t size)
{
    static_assert(static_cast<int>(nos::memory::compare_result::lesser) == -1);
    static_assert(static_cast<int>(nos::memory::compare_result::equals) == 0);
    static_assert(static_cast<int>(nos::memory::compare_result::greater) == 1);
    
    return static_cast<int>(nos::memory::compare(destination, source, size));
}

#endif
