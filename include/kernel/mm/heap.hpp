#pragma once

#include <mm/heap_allocator.hpp>

namespace nos {

class heap
{
public:
    inline static heap* get_active();

public:
    heap() = default;
    ~heap();

    heap(heap&& other);
    heap& operator=(heap&& other);

    heap(const heap&) = delete;
    heap& operator=(const heap&) = delete;

    void init(pmm& pmm);

    constexpr heap_allocator_t& get_allocator();
    constexpr kmalloc_heap_allocator_t& get_kmalloc_allocator();

private:
    heap_allocator_t _allocator;
    kmalloc_heap_allocator_t _kmalloc_allocator;

private:
    inline static heap* _active{nullptr};
};

inline heap* heap::get_active()
{
    return _active;
}

constexpr heap_allocator_t& heap::get_allocator()
{
    return _allocator;
}

constexpr kmalloc_heap_allocator_t& heap::get_kmalloc_allocator()
{
    return _kmalloc_allocator;
}

} // namespace nos
