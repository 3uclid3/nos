#pragma once

namespace NOS::Range {

template<typename TRange>
constexpr auto* data(TRange&& range);

template<typename TRange>
constexpr auto* data(TRange&& range)
{
    return range.data();
}

} // namespace NOS::Range
