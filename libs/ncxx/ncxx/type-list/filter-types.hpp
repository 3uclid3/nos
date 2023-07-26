#pragma once

#include <ncxx/type-list/concatenate-type-lists.hpp>

namespace NOS {

template<typename...>
struct TypeList;

template<template<typename TFilteredType> typename TFilter, typename... TTypes>
struct FilterTypes;

template<template<typename TFilteredType> typename TFilter>
struct FilterTypes<TFilter>
{
    using Type = TypeList<>;
};

template<bool PASSED_FILTER, template<typename TFilteredType> typename TFilter, typename THead, typename... TTails>
struct FilterTypesConditional : ConcatenateTypeLists<TypeList<THead>, typename FilterTypes<TFilter, TTails...>::Type>
{
};

template<template<typename TFilteredType> typename TFilter, typename THead, typename... TTails>
struct FilterTypesConditional<false, TFilter, THead, TTails...> : FilterTypes<TFilter, TTails...>
{
};

template<template<typename TFilteredType> typename TFilter, typename THead, typename... TTails>
struct FilterTypes<TFilter, THead, TTails...> : FilterTypesConditional<TFilter<THead>::Value, TFilter, THead, TTails...>
{
};

template<template<typename TFilteredType> typename TFilter, typename... TTypes>
using FilterTypesT = typename FilterTypes<TFilter, TTypes...>::Type;

} // namespace NOS
