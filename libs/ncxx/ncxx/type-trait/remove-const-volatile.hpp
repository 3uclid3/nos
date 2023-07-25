#pragma once

#include <ncxx/type-trait/remove-const.hpp>
#include <ncxx/type-trait/remove-volatile.hpp>

namespace NOS {

template<typename T>
struct RemoveConstVolatile
{
    using Type = RemoveConstT<RemoveVolatileT<T>>;
};

template<typename T>
using RemoveConstVolatileT = typename RemoveConstVolatile<T>::Type;

} // namespace NOS
