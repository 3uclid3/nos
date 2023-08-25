#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-trait/conditional.hpp>

namespace NOS::Details {

template<class T>
using ArraySizeTypeT = ConditionalT<sizeof(T) < 4 && sizeof(void*) >= 8, u64_t, u32_t>;

} // namespace NOS::Details
