#pragma once

#include <ncxx/type-trait/type-for-bytes.hpp>

namespace NOS {

template<Signed TSigned, typename... TTypes>
struct TypeForBytesFromTypes
{
    static constexpr size_t size = (sizeof(TTypes) + ... + 0);

    using Type = TypeForBytesT<size, TSigned>;
};

template<Signed TSigned, typename... TTypes>
using TypeForBytesFromTypesT = typename TypeForBytesFromTypes<TSigned, TTypes...>::Type;

} // namespace NOS
