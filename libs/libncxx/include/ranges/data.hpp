#pragma once

namespace NOS::Ranges {

template<typename Range>
constexpr auto* data(Range&& range);

template<typename Range>
constexpr auto* data(Range&& range)
{
    return range.data();
}

} // namespace NOS::Ranges
