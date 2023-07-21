#pragma once

#include <type-traits/is-same.hpp>

namespace N {

namespace Details {

template<class T0, class T1>
concept SameAs = IsSameV<T0, T1>;

} // namespace Details

template<typename T0, typename T1>
concept SameAs = (details::SameAs<T0, T1> && details::SameAs<T1, T0>);

} // namespace N
