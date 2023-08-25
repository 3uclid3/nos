#pragma once

#include <ncxx/type-trait/integral-constant.hpp>

namespace NOS {

template<class T>
struct IsTriviallyCopyable : public BoolConstant<__is_trivially_copyable(T)>
{};

template<class T>
inline constexpr bool IsTriviallyCopyableV = IsTriviallyCopyable<T>::Value;

} // namespace NOS
