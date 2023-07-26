#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/types-size.hpp>

namespace NOS {

template<typename...>
struct TypeList;

template<typename TTypeList>
struct TypeListSize;

template<typename... TTypes>
struct TypeListSize<TypeList<TTypes...>> : TypesSize<TTypes...>
{
};

template<typename TTypeList>
constexpr size_t TypeListSizeV{TypeListSize<TTypeList>::Value};

} // namespace NOS
