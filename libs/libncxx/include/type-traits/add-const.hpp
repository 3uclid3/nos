#pragma once

namespace NOS {

template<class T>
struct AddConst
{
    using Type = const T;
};

template<class T>
using AddConstT = typename AddConst<T>::Type;

} // namespace NOS
