#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS::Details {

template<typename TTarget, size_t TIndex, typename... TTypes>
struct IndexOfFromTypesImpl;

template<typename TTarget, size_t TIndex, typename THead>
struct IndexOfFromTypesImpl<TTarget, TIndex, THead>
{
};

template<typename TTarget, size_t TIndex>
struct IndexOfFromTypesImpl<TTarget, TIndex, TTarget> : IntegralConstant<size_t, TIndex>
{
};

template<typename TTarget, size_t TIndex, typename THead, typename... TTails>
struct IndexOfFromTypesImpl<TTarget, TIndex, THead, TTails...>
    : IndexOfFromTypesImpl<TTarget, TIndex, THead>, IndexOfFromTypesImpl<TTarget, TIndex + 1, TTails...>
{
};

} // namespace NOS::Details
