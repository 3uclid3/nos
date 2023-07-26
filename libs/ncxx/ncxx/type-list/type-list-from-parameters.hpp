#pragma once

#include <ncxx/type-list/details/type-list-from-parameters-impl.hpp>

namespace NOS {

template<typename TInvokable>
struct TypeListFromParameters : public Details::TypeListFromParametersImpl<TInvokable>
{
};

template<typename INVOCABLE>
using TypeListFromParametersT = typename TypeListFromParameters<INVOCABLE>::Type;

} // namespace NOS
