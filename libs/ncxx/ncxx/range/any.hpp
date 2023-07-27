#pragma once

#include <ncxx/algorithm/any.hpp>
#include <ncxx/range/iterator.hpp>

namespace NOS::Range {

template<typename R, typename TValue>
constexpr auto any(R& range, const TValue& value)
{
    return NOS::any(begin(range), end(range), value);
}

} // namespace NOS::Range
