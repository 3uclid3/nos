#pragma once

#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsRValueReference : BoolConstant<__is_rvalue_reference(T)>
{};

template<typename T>
inline constexpr bool IsRValueReferenceV = IsRValueReference<T>::Value;

} // namespace NOS
