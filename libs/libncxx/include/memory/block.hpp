#pragma once

#include <algorithm/min.hpp>
#include <base-types.hpp>

namespace NOS::Memory {

struct Block;
struct ConstBlock;

struct Block
{
    void* pointer;
    size_t size;

    constexpr bool operator==(const Block&) const = default;

    constexpr operator ConstBlock() const;
};

struct ConstBlock
{
    const void* pointer;
    size_t size;

    constexpr bool operator==(const ConstBlock&) const = default;
};

inline constexpr Block nullblk{nullptr, 0};

int compare(ConstBlock lhs, ConstBlock rhs);
int compare(ConstBlock lhs, ConstBlock rhs, size_t size);

void copy(Block destination, ConstBlock source);
void copy(Block destination, ConstBlock source, size_t size);

void move(Block destination, ConstBlock source);
void move(Block destination, ConstBlock source, size_t size);

void set(Block destination, byte value);
void set(Block destination, byte value, size_t size);

constexpr Block::operator ConstBlock() const
{
    return ConstBlock{pointer, size};
}

inline int compare(Block lhs, Block rhs)
{
    return compare(lhs, rhs, min(lhs.size, rhs.size));
}

inline int compare(Block lhs, Block rhs, size_t size)
{
    return __builtin_memcmp(lhs.pointer, rhs.pointer, size);
}

inline void copy(Block destination, ConstBlock source)
{
    copy(destination, source, min(destination.size, source.size));
}

inline void copy(Block destination, ConstBlock source, size_t size)
{
    __builtin_memcpy(destination.pointer, source.pointer, size);
}

inline void move(Block destination, ConstBlock source)
{
    move(destination, source, min(destination.size, source.size));
}

inline void move(Block destination, ConstBlock source, size_t size)
{
    __builtin_memmove(destination.pointer, source.pointer, size);
}

inline void set(Block destination, byte value)
{
    set(destination, value, destination.size);
}

inline void set(Block destination, byte value, size_t size)
{
    __builtin_memset(destination.pointer, static_cast<int>(size), static_cast<unsigned long>(value));
}

} // namespace NOS::Memory
