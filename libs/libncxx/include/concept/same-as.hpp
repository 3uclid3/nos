#pragma once

#include <type-traits/is-same.hpp>

namespace N {

namespace Details {

template<class T0, class T1>
concept is_same = is_same_v<T0, T1>;

} // namespace Details

template<typename T0, typename T1>
concept same_as = (details::is_same<T0, T1> && details::is_same<T1, T0>);

} // namespace N
