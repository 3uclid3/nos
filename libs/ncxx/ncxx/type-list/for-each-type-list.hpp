#pragma once

#include <ncxx/type-list/details/for-each-type-list-impl.hpp>

namespace NOS {

template<typename TTypeList, typename TFunctor>
constexpr void forEachTypeList(TFunctor&& functor)
{
    Details::ForEachTypeListImpl<TTypeList>::calls(functor);
}

} // namespace NOS
