#pragma once

#include <ncxx/type-trait/add-const.hpp>
#include <ncxx/type-trait/add-lvalue-reference.hpp>
#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct IsCopyConstructible : BoolConstant<__is_constructible(T, AddLValueReferenceT<AddConstT<T>>)>
{};

template<typename T>
inline constexpr bool IsCopyConstructibleV = IsCopyConstructible<T>::Value;

} // namespace NOS
