#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-trait/tag-type.hpp>

#include <type_traits>

namespace NOS::Details {

template<size_t TBitsCount, Signed TSigned>
constexpr decltype(auto) getTypeForBits()
{
    if (TBitsCount > 0)
    {
        if constexpr (TBitsCount <= sizeof(u8_t) * 8)
        {
            if constexpr (TSigned == Signed::Yes)
            {
                return TagType<s8_t>();
            }
            else if constexpr (TSigned == Signed::No)
            {
                return TagType<u8_t>();
            }
        }
        else if constexpr (TBitsCount <= sizeof(u16_t) * 8)
        {
            if constexpr (TSigned == Signed::Yes)
            {
                return TagType<s16_t>();
            }
            else if constexpr (TSigned == Signed::No)
            {
                return TagType<u16_t>();
            }
        }
        else if constexpr (TBitsCount <= sizeof(u32_t) * 8)
        {
            if constexpr (TSigned == Signed::Yes)
            {
                return TagType<s32_t>();
            }
            else if constexpr (TSigned == Signed::No)
            {
                return TagType<u32_t>();
            }
        }
        else if constexpr (TBitsCount <= sizeof(u64_t) * 8)
        {
            if constexpr (TSigned == Signed::Yes)
            {
                return TagType<s64_t>();
            }
            else if constexpr (TSigned == Signed::No)
            {
                return TagType<u64_t>();
            }
        }
    }
}

} // namespace NOS::Details
