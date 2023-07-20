#pragma once

#include <memory/allocator/utility.hpp>
#include <memory/block.hpp>
#include <static-array.hpp>

namespace nos::memory::allocator {

template<size_t TSize, alignment_t TAlignment = alignment_t{16}>
class Stack
{
public:
    static constexpr alignment_t Alignment{TAlignment};

    constexpr bool owns(Block block) const;

    constexpr Block allocate(size_t size);

    constexpr void deallocate(Block block);
    constexpr void deallocateAll();

    constexpr bool expand(Block& block, size_t size);
    constexpr bool reallocate(Block& block, size_t size);

private:
    constexpr bool isLastAllocatedBlock(Block block) const;

private:
    StaticArray<u8_t, TSize> _data;
    u8_t* _pointer{_data};
};

template<size_t TSize, alignment_t TAlignment>
constexpr bool Stack<TSize, TAlignment>::owns(Block block) const
{
    return block.pointer >= _data.begin() && block.pointer < _data.end();
}

template<size_t TSize, alignment_t TAlignment>
constexpr Block Stack<TSize, TAlignment>::allocate(size_t size)
{
    if (size == 0)
    {
        return nullblk;
    }

    const size_t alignedSize = roundToAlignment(size, Alignment);

    u8_t* endPointer = _pointer + alignedSize;

    if (endPointer > _data.end())
    {
        return nullblk;
    }

    Block block{_pointer, alignedSize};

    _pointer = endPointer;

    return block;
}

template<size_t TSize, alignment_t TAlignment>
constexpr void Stack<TSize, TAlignment>::deallocate(Block block)
{
    if (block == nullblk)
    {
        return;
    }

    if (isLastAllocatedBlock(block))
    {
        _pointer = block.pointer;
    }
}

template<size_t TSize, alignment_t TAlignment>
constexpr void Stack<TSize, TAlignment>::deallocateAll()
{
    _pointer = _block;
}

template<size_t TSize, alignment_t TAlignment>
constexpr bool Stack<TSize, TAlignment>::expand(Block& block, size_t size)
{
    if (size == 0)
    {
        return true;
    }
}

template<size_t TSize, alignment_t TAlignment>
constexpr bool Stack<TSize, TAlignment>::reallocate(Block& block, size_t size);
{
    if (block.size == size)
    {
        return true;
    }

    if (size == 0)
    {
        deallocate(block);

        block = nullblk;

        return true;
    }

    if (block == nullblk)
    {
        block = allocate(size);
        return true;
    }

    const size_t alignedSize = roundToAlignment(size, Alignment);

    if (isLastAllocatedBlock(block))
    {
        u8_t* endPointer = _pointer + alignedSize;

        if (endPointer > _data.end())
        {
            return false;
        }

        block.size = alignedSize;

        _pointer = endPointer;

        return true;
    }

    if (alignedSize < block.size)
    {
        block.size = alignedSize;
        return true;
    }

    Block newBlock = allocate(alignedSize);

    if (newBlock != nullblk)
    {
        copy(newBlock, block);
        
        block = newBlock;

        return true;
    }

    return false;
}

template<size_t TSize, alignment_t TAlignment>
constexpr bool Stack<TSize, TAlignment>::isLastAllocatedBlock(Block block) const
{
    return _pointer == block.pointer + block.size;
}

} // namespace nos::memory::allocator
