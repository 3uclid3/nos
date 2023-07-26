#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-trait/type-for-bits.hpp>

namespace NOS {

template<size_t TBytesCount, Signed TSigned>
struct TypeForBytes : TypeForBits<TBytesCount * 8, TSigned>
{
};

template<size_t TBytesCount, Signed TSigned>
using TypeForBytesT = typename TypeForBytes<TBytesCount, TSigned>::Type;

} // namespace NOS
