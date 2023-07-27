#pragma once

#include <ncxx/algorithm/all.hpp>
#include <ncxx/range/iterator.hpp>

namespace NOS::Range {

template<typename R, typename TValue>
constexpr bool all(R& range, const TValue& value)
{
    return NOS::all(begin(range), end(range), value);
}

} // namespace NOS::Range
