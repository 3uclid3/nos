#pragma once

#include <ncxx/algorithm/find-if.hpp>

namespace NOS::Range {

template<typename R, typename P>
constexpr auto findIf(R& range, P predicate)
{
    return NOS::findIf(range.begin(), range.end(), predicate);
}

} // namespace NOS::Range
