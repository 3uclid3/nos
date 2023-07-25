#pragma once

namespace NOS {

template<class T>
struct RemoveReference
{
    using Type = T;
};

template<class T>
struct RemoveReference<T&>
{
    using Type = T;
};

template<class T>
struct RemoveReference<T&&>
{
    using Type = T;
};

template<typename T>
using RemoveReferenceT = typename RemoveReference<T>::Type;

} // namespace NOS
