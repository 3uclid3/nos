#pragma once

#include <ncxx/type-trait/is-same.hpp>

namespace NOS {

namespace Details {

template<class T0, class T1>
concept SameAs = IsSameV<T0, T1>;

} // namespace Details

template<typename T0, typename T1>
concept SameAs = (Details::SameAs<T0, T1> && Details::SameAs<T1, T0>);

} // namespace NOS
