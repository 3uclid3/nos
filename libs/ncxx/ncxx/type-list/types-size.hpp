#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<typename... TTypes>
struct TypesSize : IntegralConstant<size_t, sizeof...(TTypes)>
{
};

template<typename... TTypes>
constexpr size_t TypesSizeV{TypesSize<TTypes...>::Value};

} // namespace NOS
