#pragma once

namespace NOS::Range {

template<typename TRange>
constexpr auto size(TRange&& range);

template<typename TRange>
constexpr auto size(TRange&& range)
{
    return range.size();
}

} // namespace NOS::Range
