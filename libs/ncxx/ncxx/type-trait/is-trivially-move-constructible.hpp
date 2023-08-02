#pragma once

#include <ncxx/type-trait/add-rvalue-reference.hpp>
#include <ncxx/type-trait/integral-constant.hpp>
#include <ncxx/type-trait/is-trivially-constructible.hpp>

namespace NOS {

template<typename T>
struct IsTriviallyMoveConstructible : BoolConstant<IsTriviallyConstructibleV<T, AddRValueReferenceT<const T>>>
{};

template<typename T>
inline constexpr bool IsTriviallyMoveConstructibleV = IsTriviallyMoveConstructible<T>::Value;

} // namespace NOS
