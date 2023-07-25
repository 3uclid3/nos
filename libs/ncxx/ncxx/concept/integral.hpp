#pragma once

#include <ncxx/type-trait/is-integral.hpp>

namespace NOS {

template<typename T>
concept Integral = IsIntegralV<T>;

} // namespace  NOS
