#pragma once

#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsLValueReference : BoolConstant<__is_lvalue_reference(T)>
{};

template<typename T>
inline constexpr bool IsLValueReferenceV = IsLValueReference<T>::Value;

} // namespace NOS
