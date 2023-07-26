#pragma once

#include <ncxx/type-list/concatenate-type-lists.hpp>

namespace NOS {

template<typename...>
struct TypeList;

template<template<typename TTransformedType> typename TTransform, typename TTypeList>
struct ConcatenateTransformTypeList;

template<template<typename TTransformedType> typename TTransform, typename... TTypes>
struct ConcatenateTransformTypeList<TTransform, TypeList<TTypes...>>
{
    using Type = ConcatenateTypeListsT<typename TTransform<TTypes>::Type...>;
};

template<template<typename TTransformedType> typename TTransform, typename TTypeList>
using ConcatenateTransformTypeListT = typename ConcatenateTransformTypeList<TTransform, TTypeList>::Type;

} // namespace NOS
