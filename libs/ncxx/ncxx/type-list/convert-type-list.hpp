#pragma once

namespace NOS {

template<class TFrom, template<class...> class TTo>
struct ConvertTypeList;

template<template<class...> class TFrom, class... TTypes, template<class...> class TTo>
struct ConvertTypeList<TFrom<TTypes...>, TTo>
{
    using Type = TTo<TTypes...>;
};

template<class TFrom, template<class...> class TTo>
using ConvertTypeListT = typename ConvertTypeList<TFrom, TTo>::Type;

} // namespace NOS
