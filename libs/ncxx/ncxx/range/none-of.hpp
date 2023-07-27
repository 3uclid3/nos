#pragma once

#include <ncxx/algorithm/none-of.hpp>
#include <ncxx/range/iterator.hpp>

namespace NOS::Range {

template<typename R, typename TValue>
constexpr auto noneOf(R& range, const TValue& value)
{
    return NOS::noneOf(begin(range), end(range), value);
}

} // namespace NOS::Range
