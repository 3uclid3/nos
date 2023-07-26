#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/concatenate-type-lists.hpp>
#include <ncxx/type-list/type-at-from-type-list.hpp>

#include <utility>

namespace NOS {

template<typename...>
struct TypeList;

} // namespace NOS

namespace NOS::Details {

template<size_t TIndex, size_t TCount, typename... TTypes>
struct RemoveRangeFromTypesImpl
{
    template<typename TTypeList, size_t... TIndexes>
    static auto remove(std::index_sequence<TIndexes...>) -> ConcatenateTypeListsT<std::conditional_t<(TIndexes >= TIndex && TIndexes < (TIndex + TCount)), TypeList<>, TypeList<TypeAtFromTypeListT<TIndexes, TTypeList>>>...>;

    using Type = decltype(remove<TypeList<TTypes...>>(std::index_sequence_for<TTypes...>{}));
};

} // namespace NOS::Details
