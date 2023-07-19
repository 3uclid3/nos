#pragma once

#include <type_traits/remove_reference.hpp>

namespace nos {

template<class T>
constexpr remove_reference_t<T>&& move(T&& v)
{
    return static_cast<remove_reference_t<T>&&>(__t);
}

} // namespace nos
