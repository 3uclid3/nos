#pragma once

#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename TBase, typename TDerived>
struct IsBaseOf : BoolConstant<__is_base_of(TBase, TDerived)>
{
};

template<typename TBase, typename TDerived>
inline constexpr bool IsBaseOfV = IsBaseOf<TBase, TDerived>::Value;

} // namespace NOS