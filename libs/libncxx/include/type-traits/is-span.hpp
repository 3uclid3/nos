#pragma once

#include <type-traits/integral-constant.hpp>

namespace NOS {

template<class T, size_t TSize>
class Span;

template<class _Tp>
struct IsSpan : FalseType
{};

template<class T, size_t TSize>
struct IsSpan<Span<T, TSize>> : TrueType
{};

} // namespace NOS
