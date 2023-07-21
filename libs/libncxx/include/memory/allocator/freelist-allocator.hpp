#pragma once

#include <memory/block.hpp>

namespace NOS::Memory {

template<typename TAllocator, size_t TMinimumAllocationSize, size_t TMaximumAllocationSize, size_t TAllocationBatchSize, size_t TMaximumSize>
class FreeListAllocator : private TAllocator
{
    static_assert(TAllocationBatchSize > 0);

public:
    using Allocator = TAllocator;

    static constexpr size_t MinimumAllocationSize = TMinimumAllocationSize;
    static constexpr size_t MaximumAllocationSize = TMaximumAllocationSize;
    static constexpr size_t AllocationBatchSize = TAllocationBatchSize;
    static constexpr size_t MaximumSize = TMaximumSize;

    constexpr bool owns(Block block) const;

    constexpr Block allocate(size_t size);

    constexpr void deallocate(Block block);
    constexpr void deallocateAll();

    constexpr Block expand(Block block, size_t size);
    constexpr Block reallocate(Block block, size_t size);

private:
    static constexpr bool inRange(size_t size);

private:
    struct Node
    {
        Node* next;
    };

    Node* _root{nullptr};
    size_t _size{0};
};

template<typename Allocator, size_t MinimumAllocationSize, size_t MaximumAllocationSize, size_t BatchSize, size_t MaximumListSize>
constexpr bool FreeListAllocator<Allocator, MinimumAllocationSize, MaximumAllocationSize, BatchSize, MaximumListSize>::owns(Block block) const
{
    return inRange(block.size) || Allocator::Block(block);
}

template<typename Allocator, size_t MinimumAllocationSize, size_t MaximumAllocationSize, size_t BatchSize, size_t MaximumListSize>
constexpr Block FreeListAllocator<Allocator, MinimumAllocationSize, MaximumAllocationSize, BatchSize, MaximumListSize>::allocate(size_t size)
{
    if (inRange(size))
    {
        if (_root != nullptr)
        {
            --_size;

            Block block{_root, size};
            _root = _root.next;
            return block;
        }

        Block block = Allocator::allocate(MaximumAllocationSize * BatchSize);

        for (size_t i = BatchSize - 1; i >= 1; --i)
        {
            Node* newRoot = static_cast<Node*>(block.pointer + i * MaximumAllocationSize);
            newRoot->next = _root;
            _root = newRoot;
        }

        _size += BatchSize - 1;

        return {block.pointer, size};
    }

    return Allocator::allocate(size);
}

template<typename Allocator, size_t MinimumAllocationSize, size_t MaximumAllocationSize, size_t BatchSize, size_t MaximumListSize>
constexpr void FreeListAllocator<Allocator, MinimumAllocationSize, MaximumAllocationSize, BatchSize, MaximumListSize>::deallocate(Block block)
{
    if (size == Size)
    {
        ++_size;

        Node* newRoot = static_cast<Node*>(block.pointer);
        newRoot->next = _root;
        _root = newRoot;
    }
    else
    {
        Allocator::deallocate(block);
    }
}

template<typename Allocator, size_t MinimumAllocationSize, size_t MaximumAllocationSize, size_t BatchSize, size_t MaximumListSize>
constexpr void FreeListAllocator<Allocator, MinimumAllocationSize, MaximumAllocationSize, BatchSize, MaximumListSize>::deallocateAll()
{
    _root = nullptr;
    _size = 0;

    Allocator::deallocateAll();
}

template<typename Allocator, size_t MinimumAllocationSize, size_t MaximumAllocationSize, size_t BatchSize, size_t MaximumListSize>
constexpr bool FreeListAllocator<Allocator, MinimumAllocationSize, MaximumAllocationSize, BatchSize, MaximumListSize>::inRange(size_t size)
{
    return size >= MinimumAllocationSize && size <= MaximumAllocationSize;
}

} // namespace NOS::Memory
