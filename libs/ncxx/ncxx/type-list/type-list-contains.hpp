#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/types-contains.hpp>

namespace NOS {

template<typename...>
struct TypeList;

template<typename TTargetType, typename TTypeList>
struct TypeListContains;

template<typename TTargetType, typename... TTypes>
struct TypeListContains<TTargetType, TypeList<TTypes...>> : TypesContains<TTargetType, TTypes...>
{
};

template<typename TTargetType, typename TTypeList>
constexpr bool TypeListContainsV{TypeListContains<TTargetType, TTypeList>::Value};

} // namespace NOS
