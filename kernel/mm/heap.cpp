#include <mm/heap.hpp>

#include <cassert>

namespace nos {

namespace {

struct coal_heap_allocator_initializer
{
    void init(pmm_allocator& allocator)
    {
        allocator.set_pmm(mm);
    }

    void init(auto&)
    {
    }

    pmm& mm;
};

struct coal_kmalloc_heap_allocator_initializer
{
    void init(coal::proxy_allocator<heap_allocator_t>& allocator)
    {
        allocator.set_allocator(&heap_allocator);
    }

    void init(auto&)
    {
    }

    heap_allocator_t& heap_allocator;
};

} // namespace

heap::~heap()
{
    if (_active == this)
    {
        _active = nullptr;
    }
}

heap::heap(heap&& other)
    : _allocator(std::move(other._allocator))
    , _kmalloc_allocator(std::move(other._kmalloc_allocator))
{
    if (_active == this)
    {
        _active = this;
    }
}

heap& heap::operator=(heap&& other)
{
    if (this != &other)
    {
        if (_active == &other)
        {
            _active = this;
        }

        _allocator = std::move(other._allocator);
        _kmalloc_allocator = std::move(other._kmalloc_allocator);
    }

    return *this;
}

void heap::init(pmm& mm)
{
    assert(_active == nullptr);

    coal_heap_allocator_initializer initializer{mm};
    _allocator.init(initializer);

    coal_kmalloc_heap_allocator_initializer kmalloc_initializer{_allocator};
    _kmalloc_allocator.init(kmalloc_initializer);

    _active = this;
}

} // namespace nos
