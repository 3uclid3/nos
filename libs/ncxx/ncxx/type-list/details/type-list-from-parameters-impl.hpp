#pragma once

#include <ncxx/type-list/type-list.hpp>
#include <ncxx/type-trait/is-same.hpp>
#include <ncxx/utility/declval.hpp>

namespace NOS::Details {

template<typename TReturn, typename TObject, typename... TParams>
TypeList<TParams...> getTypeListFromMemberFunction(TReturn (TObject::*)(TParams...));

template<typename TReturn, typename TObject, typename... TParams>
TypeList<TParams...> getTypeListFromMemberFunction(TReturn (TObject::*)(TParams...) const);

template<typename TInvocable>
auto getTypeListFromParameters(const TInvocable&) -> decltype(getTypeListFromMemberFunction(&TInvocable::operator()));

template<typename TReturn, typename... TParams>
TypeList<TParams...> getTypeListFromParameters(TReturn (*)(TParams...));

template<typename TInvocable>
struct TypeListFromParametersImpl
{
    using Type = decltype(getTypeListFromParameters(declval<TInvocable>()));
};

} // namespace NOS::Details
