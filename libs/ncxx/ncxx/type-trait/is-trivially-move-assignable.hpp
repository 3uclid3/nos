#pragma once

#include <ncxx/type-trait/add-rvalue-reference.hpp>
#include <ncxx/type-trait/integral-constant.hpp>
#include <ncxx/type-trait/is-trivially-assignable.hpp>

namespace NOS {

template<typename T>
struct IsTriviallyMoveAssignable : BoolConstant<IsTriviallyAssignableV<AddLValueReferenceT<T>, AddRValueReferenceT<T>>>
{};

template<typename T>
inline constexpr bool IsTriviallyMoveAssignableV = IsTriviallyMoveAssignable<T>::Value;

} // namespace NOS
