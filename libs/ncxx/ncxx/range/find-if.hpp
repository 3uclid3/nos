#pragma once

#include <ncxx/algorithm/find-if.hpp>
#include <ncxx/range/iterator.hpp>

namespace NOS::Range {

template<typename R, typename P>
constexpr auto findIf(R& range, P predicate)
{
    return NOS::findIf(begin(range), end(range), predicate);
}

} // namespace NOS::Range
