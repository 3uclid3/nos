#pragma once

#include <ncxx/type-list/type-for-bytes-from-types.hpp>

namespace NOS {

template<typename...>
struct TypeList;

template<typename TTypeList, Signed TSigned>
struct TypeForBytesFromTypeList;

template<typename... TTypes, Signed TSigned>
struct TypeForBytesFromTypeList<TypeList<TTypes...>, TSigned> : TypeForBytesFromTypes<TSigned, TTypes...>
{
};

template<typename TTypeList, Signed TSigned>
using TypeForBytesFromTypeListT = typename TypeForBytesFromTypeList<TTypeList, TSigned>::Type;

} // namespace NOS
