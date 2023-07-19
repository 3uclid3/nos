#pragma once

#include <memory/block.hpp>
#include <static_array.hpp>

namespace nos {

template<size_t Size>
class stack_allocator
{
public:
    bool is_owner_of(memory_block block) const;

    memory_block allocate(size_t size);

    void deallocate(memory_block block);
    void deallocate_all();

private:
    size_t round_to_aligned(size_t size) const;

private:
    static_array<unsigned char, Size> _block;
    unsigned char* _pointer{_block};
};

template<size_t Size>
bool stack_allocator<Size>::is_owner_of(memory_block block) const
{
    return block.pointer >= _data.begin() && block.pointer < _data.end();
}

template<size_t Size>
memory_block stack_allocator<Size>::allocate(size_t size)
{
    const size_t aligned_size = round_to_aligned(size);

    if (aligned_size > (_data.end() - _pointer))
    {
        return null_memory_block;
    }

    memory_block block{_pointer, size};
    
    _pointer += aligned_size;

    return block;
}

template<size_t Size>
void stack_allocator<Size>::deallocate(memory_block block)
{
    if (block.pointer + round_to_aligned(block.size) == _pointer)
    {
        _pointer = block.pointer;
    }
}

template<size_t Size>
void stack_allocator<Size>::deallocate_all()
{
    _pointer = _block;
}

} // namespace nos
