#pragma once

#include <ncxx/type-trait/add-rvalue-reference.hpp>
#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsMoveConstructible : BoolConstant<__is_constructible(T, AddRValueReferenceT<T>)>
{};

template<typename T>
inline constexpr bool IsMoveConstructibleV = IsMoveConstructible<T>::Value;

} // namespace NOS
