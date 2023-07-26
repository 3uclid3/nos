#pragma once

#include <ncxx/type-trait/is-lvalue-reference.hpp>
#include <ncxx/type-trait/remove-reference.hpp>

namespace NOS {

template<class T>
[[nodiscard]] constexpr T&& forward(RemoveReferenceT<T>& v)
{
    return static_cast<T&&>(v);
}

template<class T>
[[nodiscard]] constexpr T&& forward(RemoveReferenceT<T>&& v)
{
    static_assert(!IsLValueReferenceV<T>, "cannot forward an rvalue as an lvalue");
    return static_cast<T&&>(v);
}

} // namespace NOS
