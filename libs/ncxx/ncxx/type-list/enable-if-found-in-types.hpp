#pragma once

namespace NOS {

template<typename TOutputType, typename TTargetType, typename... TTypes>
struct EnableIfFoundInTypes;

template<typename TOutputType, typename TTargetType>
struct EnableIfFoundInTypes<TOutputType, TTargetType>
{
};

template<typename TOutputType, typename TTargetType, typename THeadType>
struct EnableIfFoundInTypes<TOutputType, TTargetType, THeadType>
{
};

template<typename TOutputType, typename TTargetType>
struct EnableIfFoundInTypes<TOutputType, TTargetType, TTargetType>
{
    using Type = TOutputType;
};

template<typename TOutputType, typename TTargetType, typename THeadType, typename... TTailTypes>
struct EnableIfFoundInTypes<TOutputType, TTargetType, THeadType, TTailTypes...>
    : public EnableIfFoundInTypes<TOutputType, TTargetType, THeadType>, public EnableIfFoundInTypes<TOutputType, TTargetType, TTailTypes...>
{
};

template<typename TOutputType, typename TTargetType, typename... TTypes>
using EnableIfFoundInTypesT = typename EnableIfFoundInTypes<TOutputType, TTargetType, TTypes...>::Type;

} // namespace NOS
