#pragma once

#include <ncxx/type-list/details/remove-range-from-types-impl.hpp>

namespace NOS {

template<size_t TIndex, size_t TCount, typename... TTypes>
struct RemoveRangeFromTypes
{
    using Type = typename Details::RemoveRangeFromTypesImpl<TIndex, TCount, TTypes...>::Type;
};

template<size_t TIndex, size_t TCount, typename... TTypes>
using RemoveRangeFromTypesT = typename RemoveRangeFromTypes<TIndex, TCount, TTypes...>::Type;

} // namespace NOS
