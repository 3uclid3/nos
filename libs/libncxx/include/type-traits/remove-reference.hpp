#pragma once

namespace nos {

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
using RemoveReferenceT = RemoveReference<T>::Type;

} // namespace nos
