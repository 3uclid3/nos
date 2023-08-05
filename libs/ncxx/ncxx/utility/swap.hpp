#pragma once

#include <ncxx/type-trait/is-move-assignable.hpp>
#include <ncxx/type-trait/is-move-constructible.hpp>
#include <ncxx/utility/move.hpp>

namespace NOS {

template<typename T>
requires(IsMoveAssignableV<T> && IsMoveConstructibleV<T>)
constexpr void swap(T& lhs, T& rhs)
{
    T t(move(lhs));
    lhs = move(rhs);
    rhs = move(t);
}

} // namespace NOS
