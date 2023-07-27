#pragma once

#include <ncxx/algorithm/find.hpp>
#include <ncxx/range/iterator.hpp>

namespace NOS::Range {

template<typename R, typename TValue>
constexpr auto find(R& range, const TValue& value)
{
    return NOS::find(begin(range), end(range), value);
}

} // namespace NOS::Range
