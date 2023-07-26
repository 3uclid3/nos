#pragma once

#include <ncxx/type-trait/integral-constant.hpp>
#include <ncxx/type-trait/is-convertible.hpp>
#include <ncxx/type-trait/is-enum.hpp>
#include <ncxx/type-trait/underlying-type.hpp>

namespace NOS {

namespace Details {

template<class T, bool = IsEnumV<T>>
struct IsEnumClassImpl;

template<class T>
struct IsEnumClassImpl<T, false> : FalseType
{};

template<class T>
struct IsEnumClassImpl<T, true> : BoolConstant<!IsConvertibleV<T, UnderlyingTypeT<T>>>
{
};

} // namespace Details

template<typename T>
struct IsEnumClass : Details::IsEnumClassImpl<T>
{};

template<class T>
inline constexpr bool IsEnumClassV = IsEnumClass<T>::Value;

} // namespace NOS
