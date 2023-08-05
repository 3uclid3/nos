#pragma once

#include <ncxx/type-trait/conditional.hpp>

namespace NOS::Details {

template<typename T>
constexpr bool IsArrayParamByValueV = sizeof(T) <= 2 * sizeof(void*);

template<typename T>
using ArrayParamTypeT = ConditionalT<IsArrayParamByValueV<T>, T, const T&>;

} // namespace NOS::Details
