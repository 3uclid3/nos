#pragma once

#include <type-traits/remove-const.hpp>
#include <type-traits/remove-volatile.hpp>

namespace NOS {

template<typename T>
struct RemoveConstVolatile
{
    using Type = RemoveConstT<RemoveVolatileT<T>>;
};

template<typename T>
using RemoveConstVolatileT = typename RemoveConstVolatile<T>::Type;

} // namespace NOS
