#pragma once

#include <ncxx/basic-types.hpp>

namespace NOS {

template<size_t TIndex, typename THead, typename... TTails>
struct TypeAtFromTypes : TypeAtFromTypes<TIndex - 1, TTails...>
{
};

template<typename THead, typename... TTails>
struct TypeAtFromTypes<0, THead, TTails...>
{
    using Type = THead;
};

template<size_t TIndex, typename THead, typename... TTails>
using TypeAtFromTypesT = typename TypeAtFromTypes<TIndex, THead, TTails...>::Type;

} // namespace NOS
