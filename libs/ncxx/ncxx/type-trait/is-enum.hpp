#pragma once

#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<class T>
struct IsEnum : public BoolConstant<__is_enum(T)>
{};

template<class T>
inline constexpr bool IsEnumV = IsEnum<T>::Value;

} // namespace NOS
