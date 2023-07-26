#pragma once

#include <ncxx/type-list/details/for-each-types-impl.hpp>

namespace NOS {

template<typename... TTypes, typename TFunctor>
constexpr void forEachTypes(TFunctor&& functor)
{
    Details::ForEachTypesImpl<TTypes...>::calls(functor);
}

} // namespace NOS
