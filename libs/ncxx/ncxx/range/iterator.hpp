#pragma once

namespace NOS::Range {

template<typename R>
auto begin(R& range)
{
    return range.begin();
}

template<typename R>
auto end(R& range)
{
    return range.end();
}

template<typename R>
auto cbegin(const R& range)
{
    return range.cbegin();
}

template<typename R>
auto cend(const R& range)
{
    return range.cend();
}

} // namespace NOS::Range
