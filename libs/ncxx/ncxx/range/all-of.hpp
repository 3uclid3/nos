#pragma once

#include <ncxx/algorithm/all-of.hpp>
#include <ncxx/range/iterator.hpp>

namespace NOS::Range {

template<typename R, typename TValue>
constexpr bool allOf(R& range, const TValue& value)
{
    return NOS::allOf(begin(range), end(range), value);
}

} // namespace NOS::Range
