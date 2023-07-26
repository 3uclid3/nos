#pragma once

#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsReference : BoolConstant<__is_reference(T)>
{};

template<typename T>
inline constexpr bool IsReferenceV = IsReference<T>::Value;

} // namespace NOS
