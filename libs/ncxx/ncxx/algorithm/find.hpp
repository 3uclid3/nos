#pragma once

namespace NOS {

template<typename I, typename TValue>
constexpr auto find(I begin, I end, const TValue& value)
{
    for (I it = begin; it != end; ++it)
    {
        if (*it == value)
        {
            return it;
        }
    }

    return end;
}

} // namespace NOS
