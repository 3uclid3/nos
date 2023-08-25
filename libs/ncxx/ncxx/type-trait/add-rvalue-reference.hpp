#pragma once

namespace NOS {

template<class T>
struct AddRValueReference
{
    using Type = __add_rvalue_reference(T);
};

template<class T>
using AddRValueReferenceT = typename AddRValueReference<T>::Type;

} // namespace NOS
