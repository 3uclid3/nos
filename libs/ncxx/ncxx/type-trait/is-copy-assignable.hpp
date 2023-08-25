#pragma once

#include <ncxx/type-trait/add-const.hpp>
#include <ncxx/type-trait/add-lvalue-reference.hpp>
#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsCopyAssignable : BoolConstant<__is_assignable(AddLValueReferenceT<T>, AddLValueReferenceT<AddConstT<T>>)>
{};

template<typename T>
inline constexpr bool IsCopyAssignableV = IsCopyAssignable<T>::Value;

} // namespace NOS
