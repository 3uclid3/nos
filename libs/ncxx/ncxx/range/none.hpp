#pragma once

#include <ncxx/algorithm/none.hpp>
#include <ncxx/range/iterator.hpp>

namespace NOS::Range {

template<typename R, typename TValue>
constexpr auto none(R& range, const TValue& value)
{
    return NOS::none(begin(range), end(range), value);
}

} // namespace NOS::Range
