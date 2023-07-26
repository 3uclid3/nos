#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-trait/is-integral.hpp>

#if !__has_builtin(__make_integer_seq)
#error "MakeIntegerSequence must be implemented"
#endif
namespace NOS {

template<typename T, T... TValues>
struct IntegerSequence
{
    using ValueType = T;

    static_assert(IsIntegralV<T>, "IntegerSequence can only be instantiated with an integral type");
    static constexpr size_t size() { return sizeof...(TValues); }
};

template<size_t... TValues>
using IndexSequence = IntegerSequence<size_t, TValues...>;

template<typename T, T TSize>
using MakeIntegerSequence = __make_integer_seq<IntegerSequence, T, TSize>;

template<size_t TSize>
using MakeIndexSequence = MakeIntegerSequence<size_t, TSize>;

template<typename... Ts>
using IndexSequenceFor = MakeIndexSequence<sizeof...(Ts)>;

} // namespace NOS
