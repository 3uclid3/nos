#pragma once

namespace NOS {

template<typename I, typename TValue>
constexpr bool any(I begin, I end, const TValue& value)
{
    for (I it = begin; it != end; ++it)
    {
        if (*it == value)
        {
            return true;
        }
    }

    return false;
}

} // namespace NOS
