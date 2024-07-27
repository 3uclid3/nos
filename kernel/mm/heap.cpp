#include <mm/heap.hpp>

#include <cassert>

namespace nos {

namespace {

struct coal_initializer
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

} // namespace

heap::~heap()
{
    if (_active_allocator == &_allocator)
    {
        _active_allocator = nullptr;
    }
}

heap::heap(heap&& other)
    : _allocator(std::move(other._allocator))
{
    if (_active_allocator == &other._allocator)
    {
        _active_allocator = &_allocator;
    }
}

heap& heap::operator=(heap&& other)
{
    if (this != &other)
    {
        if (_active_allocator == &other._allocator)
        {
            _active_allocator = &_allocator;
        }

        _allocator = std::move(other._allocator);
    }

    return *this;
}

void heap::init(pmm& mm)
{
    assert(_active_allocator == nullptr);

    coal_initializer initializer{mm};
    _allocator.init(initializer);

    _active_allocator = &_allocator;
}

} // namespace nos
