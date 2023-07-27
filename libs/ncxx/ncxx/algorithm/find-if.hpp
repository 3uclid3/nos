#pragma once

namespace NOS {

template<typename I, typename P>
constexpr auto findIf(I begin, I end, P predicate)
{
    for (I it = begin; it != end; ++it)
    {
        if (predicate(*it))
        {
            return it;
        }
    }

    return end;
}

} // namespace NOS
