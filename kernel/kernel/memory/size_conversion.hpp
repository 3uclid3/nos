#pragma once

#include <kernel/def.hpp>

// TODO move to nxx

namespace nos {

inline static constexpr size_t kilobyte{1024};
inline static constexpr size_t megabyte{kilobyte * 1024};
inline static constexpr size_t gigabyte{megabyte * 1024};

constexpr size_t bytes_to_kilobytes(size_t bytes)
{
    return bytes / kilobyte;
}

constexpr size_t kilobytes_to_bytes(size_t kilobytes)
{
    return kilobytes * kilobyte;
}

constexpr size_t bytes_to_megabytes(size_t bytes)
{
    return bytes / megabyte;
}

constexpr size_t megabytes_to_bytes(size_t megabytes)
{
    return megabytes * megabyte;
}

constexpr size_t bytes_to_gigabytes(size_t bytes)
{
    return bytes / gigabyte;
}

constexpr size_t gigabytes_to_bytes(size_t gigabytes)
{
    return gigabytes * gigabyte;
}

constexpr size_t kilobytes_to_megabytes(size_t kilobytes)
{
    return kilobytes / kilobyte;
}

constexpr size_t megabytes_to_kilobytes(size_t megabytes)
{
    return megabytes * kilobyte;
}

constexpr size_t kilobytes_to_gigabytes(size_t kilobytes)
{
    return kilobytes / gigabyte;
}

constexpr size_t gigabytes_to_kilobytes(size_t gigabytes)
{
    return gigabytes * gigabyte;
}

constexpr size_t megabytes_to_gigabytes(size_t megabytes)
{
    return megabytes / kilobyte;
}

constexpr size_t gigabytes_to_megabytes(size_t gigabytes)
{
    return gigabytes * kilobyte;
}

constexpr size_t operator"" _kb(unsigned long long kilobytes)
{
    return kilobytes_to_bytes(static_cast<size_t>(kilobytes));
}

constexpr size_t operator"" _mb(unsigned long long megabytes)
{
    return megabytes_to_bytes(static_cast<size_t>(megabytes));
}

constexpr size_t operator"" _gb(unsigned long long gigabytes)
{
    return gigabytes_to_bytes(static_cast<size_t>(gigabytes));
}

} // namespace nos
