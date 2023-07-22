#pragma once

namespace NOS {

template<class T>
struct RemoveVolatile
{
    using Type = T;
};

template<class T>
struct RemoveVolatile<volatile T>
{
    using Type = T;
};

template<class T>
using RemoveVolatileT = typename RemoveVolatile<T>::Type;

} // namespace NOS
