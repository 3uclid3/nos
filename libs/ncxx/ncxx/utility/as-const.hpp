#pragma once

#include <ncxx/type-trait/add-const.hpp>

namespace NOS {

template<class T>
constexpr AddConstT<T>& asConst(T& v)
{
    return v;
}

template<class T>
void asConst(const T&&) = delete;

} // namespace NOS
