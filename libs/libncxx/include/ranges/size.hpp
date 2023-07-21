#pragma once

namespace N::ranges {

template<typename Range>
constexpr auto size(Range&& range);

template<typename Range>
constexpr auto size(Range&& range)
{
    return range.size();
}

} // namespace N::ranges
