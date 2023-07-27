#pragma once

namespace NOS {

template<typename I>
auto begin(I& i)
{
    return i.begin();
}

template<typename I>
auto end(I& i)
{
    return i.end();
}

template<typename I>
auto cbegin(const I& i)
{
    return i.cbegin();
}

template<typename I>
auto cend(const I& i)
{
    return i.cend();
}

} // namespace NOS::Range
