#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/index-of-from-types.hpp>

namespace NOS {

template<typename...>
struct TypeList;

template<typename TTarget, typename TTypeList>
struct IndexOfFromTypeList;

template<typename TTarget, typename... TTypes>
struct IndexOfFromTypeList<TTarget, TypeList<TTypes...>> : IndexOfFromTypes<TTarget, TTypes...>
{
};

template<typename TTarget, typename TTypeList>
constexpr size_t IndexOfFromTypeListV{IndexOfFromTypeList<TTarget, TTypeList>::Value};

} // namespace NOS
