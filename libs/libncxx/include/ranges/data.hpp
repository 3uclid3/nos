#pragma once

namespace N::ranges {

template<typename Range>
constexpr auto* data(Range&& range);

template<typename Range>
constexpr auto* data(Range&& range)
{
    return range.data();
}

} // namespace N::ranges