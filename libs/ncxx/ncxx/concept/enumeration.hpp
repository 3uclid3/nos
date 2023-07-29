#pragma once

#include <ncxx/type-trait/is-enum.hpp>

namespace NOS {

template<typename T>
concept Enumeration = IsEnumV<T>;

} // namespace  NOS
