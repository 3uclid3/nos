#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-trait/details/get-type-for-bits.hpp>

namespace NOS {

template<size_t BITS_COUNT, Signed TSigned>
struct TypeForBits
{
    using Type = typename decltype(Details::getTypeForBits<BITS_COUNT, TSigned>())::Type;
};

template<size_t BITS_COUNT, Signed TSigned>
using TypeForBitsT = typename TypeForBits<BITS_COUNT, TSigned>::Type;

} // namespace NOS
