#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename T>
struct BitsOf : IntegralConstant<size_t, (sizeof(T) * BitsPerByte)>
{
};

template<typename T>
inline constexpr size_t BitsOfV = BitsOf<T>::Value;
} // namespace NOS
