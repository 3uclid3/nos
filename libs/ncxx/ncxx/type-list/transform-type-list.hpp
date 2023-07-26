#pragma once

namespace NOS {

template<typename...>
struct TypeList;

template<template<typename TTransformedType> typename TTransform, typename TTypeList>
struct TransformTypeList;

template<template<typename TTransformedType> typename TTransform, typename... TTypes>
struct TransformTypeList<TTransform, TypeList<TTypes...>>
{
    using Type = TypeList<typename TTransform<TTypes>::Type...>;
};

template<template<typename TTransformedType> typename TTransform, typename TTypeList>
using TransformTypeListT = typename TransformTypeList<TTransform, TTypeList>::Type;

} // namespace NOS
