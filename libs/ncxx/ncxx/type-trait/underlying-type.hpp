#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-trait/is-enum.hpp>

namespace NOS {

namespace Details {

template<class T, bool = IsEnumV<T>>
struct UnderlyingTypeImpl;

template<class T>
struct UnderlyingTypeImpl<T, false>
{};

template<class T>
struct UnderlyingTypeImpl<T, true>
{
    using Type = __underlying_type(T);
};

} // namespace Details

template<typename T>
struct UnderlyingType
{
    using Type = Details::UnderlyingTypeImpl<T>::Type;
};

template<typename T>
using UnderlyingTypeT = UnderlyingType<T>::Type;

} // namespace NOS
