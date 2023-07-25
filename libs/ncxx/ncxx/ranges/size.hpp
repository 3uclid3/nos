#pragma once

namespace NOS::Ranges {

template<typename Range>
constexpr auto size(Range&& range);

template<typename Range>
constexpr auto size(Range&& range)
{
    return range.size();
}

} // namespace NOS::Ranges
