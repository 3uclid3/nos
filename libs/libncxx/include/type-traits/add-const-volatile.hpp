#pragma once

#include <type-traits/add-const.hpp>
#include <type-traits/add-volatile.hpp>

namespace NOS {

template<class T>
struct AddConstVolatile
{
    using Type = AddConstT<AddVolatileT<T>>;
};

template<class T>
using AddConstT = typename AddConstVolatile<T>::Type;

} // namespace NOS
