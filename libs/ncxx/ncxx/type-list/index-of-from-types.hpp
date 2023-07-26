#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-list/details/index-of-from-types-impl.hpp>

namespace NOS {

template<typename TTarget, typename... TTypes>
struct IndexOfFromTypes : Details::IndexOfFromTypesImpl<TTarget, 0, TTypes...>
{
};

template<typename TTarget, typename... TTypes>
constexpr size_t IndexOfFromTypesV{IndexOfFromTypes<TTarget, TTypes...>::Value};

} // namespace NOS
