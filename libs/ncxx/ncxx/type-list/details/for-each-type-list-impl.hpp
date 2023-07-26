#pragma once

#include <ncxx/type-list/details/for-each-types-impl.hpp>

namespace NOS {

template<typename...>
struct TypeList;

namespace Details {

template<typename TTypeList>
struct ForEachTypeListImpl;

template<typename... TTypes>
struct ForEachTypeListImpl<TypeList<TTypes...>> : ForEachTypesImpl<TTypes...>
{
};

} // namespace Details

} // namespace NOS
