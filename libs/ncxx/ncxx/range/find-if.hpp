#pragma once

#include <ncxx/algorithm/find-if.hpp>

namespace NOS::Range {

template<typename TRange, typename P>
constexpr auto findIf(TRange&& range, P predicate)
{
    return NOS::findIf(range.begin(), range.end(), predicate);
}

} // namespace NOS::Range
