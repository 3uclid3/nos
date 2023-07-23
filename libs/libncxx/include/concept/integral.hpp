#pragma once

#include <type-traits/is-integral.hpp>

namespace NOS {

template<typename T>
concept Integral = IsIntegralV<T>;

} // namespace  NOS
