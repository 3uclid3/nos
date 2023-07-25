#pragma once

#include <ncxx/type-trait/add-const.hpp>
#include <ncxx/type-trait/add-volatile.hpp>

namespace NOS {

template<class T>
struct AddConstVolatile
{
    using Type = AddConstT<AddVolatileT<T>>;
};

template<class T>
using AddConstT = typename AddConstVolatile<T>::Type;

} // namespace NOS
