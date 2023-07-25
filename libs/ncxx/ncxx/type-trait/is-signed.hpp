#pragma once

#include <ncxx/type-trait/integral-constant.hpp>
#include <ncxx/type-trait/is-arithmetic.hpp>
#include <ncxx/type-trait/is-integral.hpp>

namespace NOS {

namespace Details {

template<typename T, bool = IsIntegralV<T>>
struct IsSignedImpl : public BoolConstant<(T(-1) < T(0))>
{};

template<typename T>
struct IsSignedImpl<T, false> : TrueType
{}; // floating point

template<typename T, bool = IsArithmeticV<T>>
struct IsSigned : IsSignedImpl<T>
{};

template<class T>
struct IsSigned<T, false> : FalseType
{};

} // namespace Details

template<typename T>
struct IsSigned : Details::IsSigned<T>
{};

template<typename T>
inline constexpr bool IsSignedV = IsSigned<T>::Value;

} // namespace NOS
