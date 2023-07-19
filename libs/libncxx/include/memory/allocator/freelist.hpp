#pragma once

#include <memory/block.hpp>

namespace nos {

template<typename Allocator, size_t MinAllocSize, size_t MaxAllocSize, size_t BatchSize, size_t MaxListSize>
class freelist_allocator
{
public:
    bool is_owner_of(memory_block block) const;

    memory_block allocate(size_t size);

    void deallocate(memory_block block);
    void deallocate_all();

private:
    struct node
    {
        node* next;
    };

    Allocator _allocator;
    Node* _root{nullptr};
};

template<typename Allocator, size_t AllocationSize>
bool freelist_allocator<Allocator, AllocationSize>::is_owner_of(memory_block block) const
{
    return block.size == Size || _allocator.is_owner_of(block);
}

template<typename Allocator, size_t AllocationSize>
memory_block freelist_allocator<Allocator, AllocationSize>::allocate(size_t size)
{
    if (size == Size && _root != nullptr)
    {
        memory_block block{_root, Size};
        _root = _root.next;
        return block;
    }
    else
    {
        return _allocator.allocate(size);
    }
}

template<typename Allocator, size_t AllocationSize>
void freelist_allocator<Allocator, AllocationSize>::deallocate(memory_block block)
{
    if (size == Size)
    {
        node* newRoot = static_cast<node*>(block.pointer);
        newRoot->next = _root;
        _root = newRoot;
    }
    else
    {
        _allocator.deallocate(block);
    }
}

template<typename Allocator, size_t AllocationSize>
void freelist_allocator<Allocator, AllocationSize>::deallocate_all()
{
    _root = nullptr;
}

} // namespace nos
