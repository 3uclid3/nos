#pragma once

#include <ncxx/memory/address-of.hpp>
#include <ncxx/memory/new.hpp>
#include <ncxx/type-trait/is-static-array.hpp>
#include <ncxx/utility/forward.hpp>

namespace NOS::Memory {

template<typename T, typename... TArguments>
constexpr T* constructAt(T* ptr, TArguments&&... args)
{
    return ::new (static_cast<void*>(ptr)) T(forward<TArguments>(args)...);
}

template<typename T>
constexpr void destroyAt(T* ptr)
{
    if constexpr (IsStaticArrayV<T>)
    {
        for (auto& elem : *ptr)
        {
            destroyAt(addressOf(elem));
        }
    }
    else
    {
        ptr->~T();
    }
}

} // namespace NOS::Memory
