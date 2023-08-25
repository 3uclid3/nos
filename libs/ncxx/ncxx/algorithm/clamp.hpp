#pragma once

namespace NOS {

template<typename T, typename TComparator>
constexpr const T& clamp(const T& value, const T& low, const T& high, TComparator comparator)
{
    if (comparator(value, low))
    {
        return low;
    }

    if (comparator(high, value))
    {
        return high;
    }

    return value;
}

template<typename T>
constexpr const T& clamp(const T& value, const T& low, const T& high)
{
    return clamp(value, low, high, [](const T& lhs, const T& rhs) { return lhs < rhs; });
}

} // namespace NOS