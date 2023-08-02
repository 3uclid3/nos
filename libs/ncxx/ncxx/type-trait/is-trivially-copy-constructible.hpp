#pragma once

#include <ncxx/type-trait/add-lvalue-reference.hpp>
#include <ncxx/type-trait/integral-constant.hpp>
#include <ncxx/type-trait/is-trivially-constructible.hpp>

namespace NOS {

template<typename T>
struct IsTriviallyCopyConstructible : BoolConstant<IsTriviallyConstructibleV<T, AddLValueReferenceT<const T>>>
{};

template<typename T>
inline constexpr bool IsTriviallyCopyConstructibleV = IsTriviallyCopyConstructible<T>::Value;

} // namespace NOS
