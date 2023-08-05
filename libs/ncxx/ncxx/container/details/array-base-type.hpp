#pragma once

#include <ncxx/container/details/array-object.hpp>
#include <ncxx/container/details/array-trivial.hpp>
#include <ncxx/container/details/is-trivial-array.hpp>
#include <ncxx/type-trait/conditional.hpp>

namespace NOS::Details {

template<typename T, typename TAllocator, typename TSize>
using ArrayBaseTypeT = ConditionalT<IsTrivialArrayV<T>, ArrayTrivial<T, TAllocator, TSize>, ArrayObject<T, TAllocator, TSize>>;

} // namespace NOS::Details