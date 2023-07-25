#pragma once

namespace NOS {

template<class T>
struct AddPointer
{
    using Type = __add_pointer(T);
};

template<class T>
using AddPointerT = typename AddPointer<T>::Type;

} // namespace NOS
