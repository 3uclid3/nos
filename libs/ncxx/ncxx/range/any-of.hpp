#pragma once

#include <ncxx/algorithm/any-of.hpp>
#include <ncxx/range/iterator.hpp>

namespace NOS::Range {

template<typename R, typename TValue>
constexpr auto anyOf(R& range, const TValue& value)
{
    return NOS::anyOf(begin(range), end(range), value);
}

} // namespace NOS::Range
