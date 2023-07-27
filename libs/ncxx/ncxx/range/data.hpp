#pragma once

namespace NOS::Range {

template<typename R>
constexpr auto* data(R& range)
{
    return range.data();
}

template<typename R>
constexpr const auto* cdata(const R& range)
{
    return range.data();
}

} // namespace NOS::Range
