#pragma once

#include <ncxx/type-trait/add-const.hpp>
#include <ncxx/type-trait/add-lvalue-reference.hpp>
#include <ncxx/type-trait/integral-constant.hpp>
#include <ncxx/type-trait/is-trivially-assignable.hpp>

namespace NOS {

template<typename T>
struct IsTriviallyCopyAssignable : BoolConstant<IsTriviallyAssignableV<AddLValueReferenceT<T>, AddLValueReferenceT<AddConstT<T>>>>
{};

template<typename T>
inline constexpr bool IsTriviallyCopyAssignableV = IsTriviallyCopyAssignable<T>::Value;

} // namespace NOS
