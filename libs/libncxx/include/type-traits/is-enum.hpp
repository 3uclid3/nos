#pragma once

#include <type-traits/integral-constant.hpp>

namespace NOS {

template<class T>
struct IsEnum : public IntegralConstant<bool, __is_enum(T)>
{};

template<class T>
inline constexpr bool IsEnumV = IsEnum<T>::Value;

} // namespace NOS
