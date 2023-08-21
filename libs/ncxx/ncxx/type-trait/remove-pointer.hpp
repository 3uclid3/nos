#pragma once

namespace NOS {

template<class T>
struct RemovePointer
{
    using Type = T;
};

template<class T>
struct RemovePointer<T*>
{
    using Type = T;
};

template<typename T>
using RemovePointerT = typename RemovePointer<T>::Type;

} // namespace NOS
