#pragma once

namespace NOS {

template<typename I, typename P>
constexpr bool noneOf(I begin, I end, P predicate)
{
    for (I it = begin; it != end; ++it)
    {
        if (predicate(*it))
        {
            return false;
        }
    }

    return true;
}

} // namespace NOS
