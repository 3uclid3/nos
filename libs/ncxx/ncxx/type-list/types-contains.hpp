#pragma once

#include <ncxx/type-trait/integral-constant.hpp>
#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

template<typename TTargetType, typename... TTypes>
struct TypesContains : BoolConstant<(IsSameV<TTargetType, TTypes> || ...)>
{
};

template<typename TTargetType, typename... TTypes>
constexpr bool TypesContainsV{TypesContains<TTargetType, TTypes...>::Value};

} // namespace NOS
