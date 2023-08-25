#pragma once

#include <ncxx/type-trait/is-trivially-copyable.hpp>

namespace NOS {

template<class TTo, class TFrom>
requires(sizeof(TTo) == sizeof(TFrom) && IsTriviallyCopyableV<TTo> && IsTriviallyCopyableV<TFrom>)
constexpr TTo bitCast(const TFrom& from)
{
    return __builtin_bit_cast(TTo, from);

} // namespace NOS
