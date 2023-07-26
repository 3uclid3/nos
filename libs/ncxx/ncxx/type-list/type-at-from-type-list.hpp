#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/type-at-from-types.hpp>

namespace NOS {

template<typename...>
struct TypeList;

template<size_t TIndex, typename TTypeList>
struct TypeAtFromTypeList;

template<size_t TIndex, typename... TTypes>
struct TypeAtFromTypeList<TIndex, TypeList<TTypes...>> : TypeAtFromTypes<TIndex, TTypes...>
{
};

template<size_t TIndex, typename TTypeList>
using TypeAtFromTypeListT = typename TypeAtFromTypeList<TIndex, TTypeList>::Type;

} // namespace NOS
