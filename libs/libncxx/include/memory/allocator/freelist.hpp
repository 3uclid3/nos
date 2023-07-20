#pragma once

#include <memory/block.hpp>

namespace nos::memory::allocator {

template<typename Allocator, size_t MinimumAllocationSize, size_t MaximumAllocationSize, size_t BatchSize, size_t MaximumListSize>
class freelist : private Allocator
{
public:
    constexpr bool is_owner(block block) const;

    constexpr block allocate(size_t size);
    constexpr block allocate_all();

    constexpr void deallocate(block block);
    constexpr void deallocate_all();

    constexpr void expand(block& block, size_t delta_size);
    constexpr void reallocate(block& block, size_t size);

private:
    static constexpr bool in_range(size_t size);

private:
    struct node
    {
        node* next;
    };

    Node* _root{nullptr};
};

template<typename Allocator, size_t MinimumAllocationSize, size_t MaximumAllocationSize, size_t BatchSize, size_t MaximumListSize>
constexpr bool freelist<Allocator, MinimumAllocationSize, MaximumAllocationSize, BatchSize, MaximumListSize>::is_owner(block block) const
{
    return in_range(block.size) || Allocator::is_owner_of(block);
}

template<typename Allocator, size_t MinimumAllocationSize, size_t MaximumAllocationSize, size_t BatchSize, size_t MaximumListSize>
constexpr block freelist<Allocator, MinimumAllocationSize, MaximumAllocationSize, BatchSize, MaximumListSize>::allocate(size_t size)
{
    if (in_range(size))
    {
        if (_root != nullptr)
        {
            block block{_root, size};
            _root = _root.next;
            return block;
        }

        const block block{Allocator::allocate(MaximumAllocationSize * BatchSize)};

        for (size_t i = BatchSize - 1; i >= 1; --i)
        {
            node* newRoot = static_cast<node*>(block.pointer + i * MaximumAllocationSize);
            newRoot->next = _root;
            _root = newRoot;
        }

        return {block.pointer, size};
    }
    
    return Allocator::allocate(size);
}

template<typename Allocator, size_t MinimumAllocationSize, size_t MaximumAllocationSize, size_t BatchSize, size_t MaximumListSize>
constexpr block freelist<Allocator, MinimumAllocationSize, MaximumAllocationSize, BatchSize, MaximumListSize>::allocate_all()
{
    return Allocator::allocate_all();
}

template<typename Allocator, size_t MinimumAllocationSize, size_t MaximumAllocationSize, size_t BatchSize, size_t MaximumListSize>
constexpr void freelist<Allocator, MinimumAllocationSize, MaximumAllocationSize, BatchSize, MaximumListSize>::deallocate(block block)
{
    if (size == Size)
    {
        node* newRoot = static_cast<node*>(block.pointer);
        newRoot->next = _root;
        _root = newRoot;
    }
    else
    {
        Allocator::deallocate(block);
    }
}

template<typename Allocator, size_t MinimumAllocationSize, size_t MaximumAllocationSize, size_t BatchSize, size_t MaximumListSize>
constexpr void freelist<Allocator, MinimumAllocationSize, MaximumAllocationSize, BatchSize, MaximumListSize>::deallocate_all()
{
    _root = nullptr;
    
    Allocator::deallocate_all();
}

template<typename Allocator, size_t MinimumAllocationSize, size_t MaximumAllocationSize, size_t BatchSize, size_t MaximumListSize>
constexpr bool freelist<Allocator, MinimumAllocationSize, MaximumAllocationSize, BatchSize, MaximumListSize>::in_range(size_t size)
{
    return size >= MinimumAllocationSize && size <= MaximumAllocationSize;
}

} // namespace nos::memory::allocator
