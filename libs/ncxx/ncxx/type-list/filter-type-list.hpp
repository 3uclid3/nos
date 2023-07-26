#pragma once

#include <ncxx/type-list/filter-types.hpp>

namespace NOS {

template<template<typename TFilteredType> typename TFilter, typename TTypeList>
struct FilterTypeList;

template<template<typename TFilteredType> typename TFilter, typename... TTypes>
struct FilterTypeList<TFilter, TypeList<TTypes...>> : FilterTypes<TFilter, TTypes...>
{
};

template<template<typename TFilteredType> typename TFilter, typename TTypeList>
using FilterTypeListT = typename FilterTypeList<TFilter, TTypeList>::Type;

} // namespace NOS
