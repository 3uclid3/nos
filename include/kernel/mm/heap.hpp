#pragma once

#include <mm/heap_allocator.hpp>

namespace nos {

class heap
{
public:
    static heap& get();

public:
    heap();
    ~heap();

    heap(heap&& other) = delete;
    heap& operator=(heap&& other) = delete;

    heap(const heap&) = delete;
    heap& operator=(const heap&) = delete;

    void init(pmm& pmm);

    constexpr heap_allocator_t& get_allocator();
    constexpr kmalloc_heap_allocator_t& get_kmalloc_allocator();

private:
    heap_allocator_t _allocator;
    kmalloc_heap_allocator_t _kmalloc_allocator;

private:
    inline static heap* _instance{nullptr};
};

inline heap& heap::get()
{
    return *_instance;
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
