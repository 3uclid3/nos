#include <mm/heap.hpp>

#include <cassert>

namespace nos {

namespace {

struct coal_heap_allocator_initializer
{
    void init(hh_pmm_allocator& allocator)
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

heap::heap()
{
    assert(_instance == nullptr);
    _instance = this;
}

heap::~heap()
{
    assert(_instance == this);
    _instance = nullptr;
}

void heap::init(pmm& mm)
{
    coal_heap_allocator_initializer initializer{mm};
    _allocator.init(initializer);

    coal_kmalloc_heap_allocator_initializer kmalloc_initializer{_allocator};
    _kmalloc_allocator.init(kmalloc_initializer);
}

} // namespace nos
