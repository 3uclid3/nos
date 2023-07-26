#pragma once

#include <ncxx/type-list/enable-if-found-in-types.hpp>

namespace NOS {

template<typename...>
struct TypeList;

template<typename TOutputType, typename TTargetType, typename TTypeList>
struct EnableIfFoundInTypeList;

template<typename TOutputType, typename TTargetType, typename... TTypes>
struct EnableIfFoundInTypeList<TOutputType, TTargetType, TypeList<TTypes...>> : public EnableIfFoundInTypes<TOutputType, TTargetType, TTypes...>
{
};

template<typename TOutputType, typename TTargetType, typename TTypeList>
using EnableIfFoundInTypeListT = typename EnableIfFoundInTypeList<TOutputType, TTargetType, TTypeList>::Type;

} // namespace NOS
