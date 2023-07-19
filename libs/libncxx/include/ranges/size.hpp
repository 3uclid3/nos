#pragma once

namespace nos::ranges {

template<typename Range>
constexpr auto size(Range&& range);

template<typename Range>
constexpr auto size(Range&& range)
{
    return range.size();
}

} // namespace nos::ranges
