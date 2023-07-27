#pragma once

namespace NOS {

template<typename I, typename P>
constexpr bool anyOf(I begin, I end, P predicate)
{
    for (I it = begin; it != end; ++it)
    {
        if (predicate(*it))
        {
            return true;
        }
    }

    return false;
}

} // namespace NOS
