#pragma once

namespace NOS {

template<class T>
struct RemoveConst
{
    using Type = T;
};

template<class T>
struct RemoveConst<const T>
{
    using Type = T;
};

template<class T>
using RemoveConstT = RemoveConst<T>::Type;

} // namespace NOS
