#pragma once

#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T, typename TArg>
struct IsTriviallyAssignable : BoolConstant<__is_trivially_assignable(T, TArg)>
{};

template<typename T, typename TArg>
inline constexpr bool IsTriviallyAssignableV = IsTriviallyAssignable<T, TArg>::Value;

} // namespace NOS
