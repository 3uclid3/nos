#pragma once

#include <ncxx/type-list/remove-range-from-types.hpp>

namespace NOS {

template<size_t TIndex, size_t TCount, typename TTypeList>
struct RemoveRangeFromTypeList;

template<size_t TIndex, size_t TCount, typename... TTypes>
struct RemoveRangeFromTypeList<TIndex, TCount, TypeList<TTypes...>> : RemoveRangeFromTypes<TIndex, TCount, TTypes...>
{
};

template<size_t TIndex, size_t TCount, typename TTypeList>
using RemoveRangeFromTypeListT = typename RemoveRangeFromTypeList<TIndex, TCount, TTypeList>::Type;

} // namespace NOS
