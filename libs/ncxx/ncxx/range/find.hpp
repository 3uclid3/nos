#pragma once

#include <ncxx/algorithm/find.hpp>

namespace NOS::Range {

template<typename R, typename TValue>
constexpr auto find(R& range, const TValue& value)
{
    return NOS::find(range.begin(), range.end(), value);
}

} // namespace NOS::Range
