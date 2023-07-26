#pragma once

namespace NOS {

template<typename...>
struct TypeList;

template<typename... TTypeLists>
struct ConcatenateTypeLists;

template<>
struct ConcatenateTypeLists<>
{
    using Type = TypeList<>;
};

template<typename... TFirsts>
struct ConcatenateTypeLists<TypeList<TFirsts...>>
{
    using Type = TypeList<TFirsts...>;
};

template<typename... TFirsts, typename... TSeconds, typename... TOthers>
struct ConcatenateTypeLists<TypeList<TFirsts...>, TypeList<TSeconds...>, TOthers...> : ConcatenateTypeLists<TypeList<TFirsts..., TSeconds...>, TOthers...>
{
};

template<typename... TTypeLists>
using ConcatenateTypeListsT = typename ConcatenateTypeLists<TTypeLists...>::Type;

} // namespace NOS
