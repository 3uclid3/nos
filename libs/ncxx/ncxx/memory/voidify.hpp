#pragma once

#include <ncxx/memory/address-of.hpp>

namespace NOS {

template<typename T>
constexpr void* voidify(T& v)
{
    return addressOf(v);
}

} // namespace NOS
