#pragma once

#include <ncxx/container/static-array.hpp>
#include <ncxx/memory/block.hpp>
#include <ncxx/memory/utility.hpp>

namespace NOS::Memory {

template<size_t TSize, alignment_t TAlignment = alignment_t{16}>
class StackAllocator
{
public:
    static constexpr size_t Size{TSize};
    static constexpr alignment_t Alignment{TAlignment};

    [[nodiscard]] constexpr bool owns(ConstBlock block) const;

    [[nodiscard]] constexpr Block allocate(size_t size);

    constexpr void deallocate(Block block);
    constexpr void deallocateAll();

    [[nodiscard]] constexpr Block expand(Block block, size_t size);
    [[nodiscard]] constexpr Block reallocate(Block block, size_t size);

private:
    constexpr bool isLastAllocatedBlock(ConstBlock block) const;

private:
    StaticArray<u8_t, TSize> _data;
    u8_t* _pointer{_data.data()};
};

template<size_t TSize, alignment_t TAlignment>
constexpr bool StackAllocator<TSize, TAlignment>::owns(ConstBlock block) const
{
    return block.pointer >= _data.begin() && block.pointer < _data.end();
}

template<size_t TSize, alignment_t TAlignment>
constexpr Block StackAllocator<TSize, TAlignment>::allocate(size_t size)
{
    if (size == 0)
    {
        return nullblk;
    }

    const size_t alignedSize = roundToAlignment(size, Alignment);

    u8_t* endPointer = reinterpret_cast<u8_t*>(reinterpret_cast<uintptr_t>(_pointer) + alignedSize);

    if (endPointer > _data.end())
    {
        return nullblk;
    }

    Block block{_pointer, alignedSize};

    _pointer = endPointer;

    return block;
}

template<size_t TSize, alignment_t TAlignment>
constexpr void StackAllocator<TSize, TAlignment>::deallocate(Block block)
{
    if (block == nullblk)
    {
        return;
    }

    if (isLastAllocatedBlock(block))
    {
        _pointer = static_cast<u8_t*>(block.pointer);
    }
}

template<size_t TSize, alignment_t TAlignment>
constexpr void StackAllocator<TSize, TAlignment>::deallocateAll()
{
    _pointer = _data;
}

template<size_t TSize, alignment_t TAlignment>
constexpr Block StackAllocator<TSize, TAlignment>::expand(Block block, size_t size)
{
    if (size == 0)
    {
        return block;
    }

    if (block == nullblk)
    {
        return allocate(size);
    }

    if (!isLastAllocatedBlock(block))
    {
        return nullblk;
    }

    const size_t alignedSize = roundToAlignment(size, Alignment);

    u8_t* endPointer = _pointer + alignedSize;

    if (endPointer > _data.end())
    {
        return nullblk;
    }

    _pointer = endPointer;

    block.size += alignedSize;

    return block;
}

template<size_t TSize, alignment_t TAlignment>
constexpr Block StackAllocator<TSize, TAlignment>::reallocate(Block block, size_t size)
{
    if (block.size == size)
    {
        return block;
    }

    if (size == 0)
    {
        deallocate(block);

        return nullblk;
    }

    if (block == nullblk)
    {
        return allocate(size);
    }

    const size_t alignedSize = roundToAlignment(size, Alignment);

    if (isLastAllocatedBlock(block))
    {
        u8_t* endPointer = _pointer + alignedSize;

        if (endPointer > _data.end())
        {
            return nullblk;
        }

        block.size = alignedSize;

        _pointer = endPointer;

        return block;
    }

    if (alignedSize < block.size)
    {
        block.size = alignedSize;
        return block;
    }

    Block newBlock = allocate(alignedSize);

    if (newBlock != nullblk)
    {
        copy(newBlock, block, block.size);

        return newBlock;
    }

    return nullblk;
}

template<size_t TSize, alignment_t TAlignment>
constexpr bool StackAllocator<TSize, TAlignment>::isLastAllocatedBlock(ConstBlock block) const
{
    return _pointer == static_cast<const u8_t*>(block.pointer) + block.size;
}

} // namespace NOS::Memory
