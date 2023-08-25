#pragma once

namespace NOS {

template<class T>
struct AddLValueReference
{
    using Type = __add_lvalue_reference(T);
};

template<class T>
using AddLValueReferenceT = typename AddLValueReference<T>::Type;

} // namespace NOS
