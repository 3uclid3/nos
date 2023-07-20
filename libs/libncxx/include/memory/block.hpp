#pragma once

#include <algorithm/min.hpp>
#include <base-types.hpp>

namespace nos::memory {

struct Block
{
    void* pointer;
    size_t size;

    bool operator==(const Block&) const = default;
};

inline constexpr Block nullblk{nullptr, 0};

constexpr int compare(Block lhs, Block rhs);
constexpr int compare(Block lhs, Block rhs, size_t size);

constexpr void copy(Block& destination, Block source);
constexpr void copy(Block& destination, Block source, size_t size);

constexpr void move(Block& destination, Block source);
constexpr void move(Block& destination, Block source, size_t size);

void set(Block& block, byte value);
void set(Block& block, byte value, size_t size);

constexpr int compare(Block lhs, Block rhs)
{
    return compare(lhs, rhs, min(lhs.size, rhs.size));
}

constexpr int compare(Block lhs, Block rhs, size_t size)
{
    return __builtin_memcmp(lhs.pointer, rhs.pointer, size);
}

constexpr void copy(Block& destination, Block source)
{
    copy(destination, source, min(destination.size, source.size));
}

constexpr void copy(Block& destination, Block source, size_t size)
{
    __builtin_memcpy(destination.pointer, source.pointer, size);
}

constexpr void move(Block& destination, Block source)
{
    move(destination, source, min(destination.size, source.size));
}

constexpr void move(Block& destination, Block source, size_t size)
{
    __builtin_memmove(destination.pointer, source.pointer, size);
}

inline void set(Block& block, byte value)
{
    set(block, value, block.size);
}

inline void set(Block& block, byte value, size_t size)
{
    __builtin_memset(block.pointer, static_cast<int>(size), static_cast<unsigned long>(value));
}

} // namespace nos::memory
