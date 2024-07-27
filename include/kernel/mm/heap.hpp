#pragma once

#include <mm/heap_allocator.hpp>

namespace nos {

class heap
{
public:
    inline static heap_allocator_t* get_active_allocator();

public:
    heap() = default;
    ~heap();

    heap(heap&& other);
    heap& operator=(heap&& other);

    heap(const heap&) = delete;
    heap& operator=(const heap&) = delete;

    void init(pmm& pmm);

    constexpr heap_allocator_t& get_allocator();

private:
    heap_allocator_t _allocator;

private:
    inline static heap_allocator_t* _active_allocator{nullptr};
};

inline heap_allocator_t* heap::get_active_allocator()
{
    return _active_allocator;
}

constexpr heap_allocator_t& heap::get_allocator()
{
    return _allocator;
}

} // namespace nos
