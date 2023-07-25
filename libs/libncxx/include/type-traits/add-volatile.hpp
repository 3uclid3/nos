#pragma once

namespace NOS {

template<class T>
struct AddVolatile
{
    using Type = volatile T;
};

template<class T>
using AddVolatileT = typename AddVolatile<T>::Type;

} // namespace NOS
