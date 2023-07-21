#pragma once

#include <type-traits/is-same.hpp>

namespace nos {

namespace details {

template<class T0, class T1>
concept SameAs = IsSameV<T0, T1>;

} // namespace details

template<typename T0, typename T1>
concept SameAs = (details::SameAs<T0, T1> && details::SameAs<T1, T0>);

} // namespace nos
