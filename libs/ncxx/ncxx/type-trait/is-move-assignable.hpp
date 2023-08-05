#pragma once

#include <ncxx/type-trait/add-lvalue-reference.hpp>
#include <ncxx/type-trait/add-rvalue-reference.hpp>
#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsMoveAssignable : BoolConstant<__is_assignable(AddLValueReferenceT<T>, AddRValueReferenceT<T>)>
{};

template<typename T>
inline constexpr bool IsMoveAssignableV = IsMoveAssignable<T>::Value;

} // namespace NOS
