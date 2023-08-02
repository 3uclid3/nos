#pragma once

#include <ncxx/type-trait/add-rvalue-reference.hpp>
#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T, typename... TArgs>
struct IsTriviallyConstructible : BoolConstant<__is_trivially_constructible(T, TArgs...)>
{};

template<typename T, typename... TArgs>
inline constexpr bool IsTriviallyConstructibleV = IsTriviallyConstructible<T, TArgs...>::Value;

} // namespace NOS
