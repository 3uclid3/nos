#pragma once

namespace nos::ranges {

template<typename Range>
constexpr auto* data(Range&& range);

template<typename Range>
constexpr auto* data(Range&& range)
{
    return range.data();
}

} // namespace nos::ranges