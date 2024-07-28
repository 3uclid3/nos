#pragma once

#include <cstddef>

namespace nos {

inline static constexpr std::size_t page_size = 0x1000;

inline static constexpr std::size_t kilobyte{1024};
inline static constexpr std::size_t megabyte{kilobyte * 1024};
inline static constexpr std::size_t gigabyte{megabyte * 1024};

constexpr std::size_t bytes_to_pages(std::size_t bytes)
{
    return (bytes + page_size - 1) / page_size;
}

constexpr std::size_t pages_to_bytes(std::size_t bytes)
{
    return bytes * page_size;
}

constexpr std::size_t bytes_to_kilobytes(std::size_t bytes)
{
    return bytes / kilobyte;
}

constexpr std::size_t kilobytes_to_bytes(std::size_t kilobytes)
{
    return kilobytes * kilobyte;
}

constexpr std::size_t bytes_to_megabytes(std::size_t bytes)
{
    return bytes / megabyte;
}

constexpr std::size_t megabytes_to_bytes(std::size_t megabytes)
{
    return megabytes * megabyte;
}

constexpr std::size_t bytes_to_gigabytes(std::size_t bytes)
{
    return bytes / gigabyte;
}

constexpr std::size_t gigabytes_to_bytes(std::size_t gigabytes)
{
    return gigabytes * gigabyte;
}

constexpr std::size_t kilobytes_to_megabytes(std::size_t kilobytes)
{
    return kilobytes / kilobyte;
}

constexpr std::size_t megabytes_to_kilobytes(std::size_t megabytes)
{
    return megabytes * kilobyte;
}

constexpr std::size_t kilobytes_to_gigabytes(std::size_t kilobytes)
{
    return kilobytes / gigabyte;
}

constexpr std::size_t gigabytes_to_kilobytes(std::size_t gigabytes)
{
    return gigabytes * gigabyte;
}

constexpr std::size_t megabytes_to_gigabytes(std::size_t megabytes)
{
    return megabytes / kilobyte;
}

constexpr std::size_t gigabytes_to_megabytes(std::size_t gigabytes)
{
    return gigabytes * kilobyte;
}

constexpr std::size_t operator"" _kb(unsigned long long kilobytes)
{
    return kilobytes_to_bytes(static_cast<std::size_t>(kilobytes));
}

constexpr std::size_t operator"" _mb(unsigned long long megabytes)
{
    return megabytes_to_bytes(static_cast<std::size_t>(megabytes));
}

constexpr std::size_t operator"" _gb(unsigned long long gigabytes)
{
    return gigabytes_to_bytes(static_cast<std::size_t>(gigabytes));
}

} // namespace nos
