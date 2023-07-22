#pragma once

#include <type-traits/is-function.hpp>

namespace NOS {

template<class T>
struct PointerTraits
{
    using Pointer = T;
};

template<typename TPtr>
constexpr auto toAddress(const TPtr& ptr);

template<typename T>
constexpr T* toAddress(T* ptr);

template<typename TPtr>
constexpr auto toAddress(const TPtr& ptr)
{
    if constexpr (requires { PointerTraits<TPtr>::toAddress(ptr); })
    {
        return PointerTraits<TPtr>::toAddress(ptr);
    }

    return toAddress(ptr.operator->());
}

template<typename T>
constexpr T* toAddress(T* ptr)
{
    static_assert(!IsFunctionV<T>);
    return ptr;
}

} // namespace NOS
