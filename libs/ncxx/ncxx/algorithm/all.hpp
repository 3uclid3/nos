#pragma once

namespace NOS {

template<typename I, typename TValue>
constexpr bool all(I begin, I end, const TValue& value)
{
    for (I it = begin; it != end; ++it)
    {
        if (*it != value)
        {
            return false;
        }
    }

    return true;
}

} // namespace NOS
