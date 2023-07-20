#pragma once

#include <algorithm/max.hpp>
#include <memory/allocator/utility.hpp>
#include <memory/block.hpp>

namespace nos::memory::allocator {

template<typename Allocator, typename Prefix, typename Suffix = void>
class affix : private Allocator
{
public:
    static constexpr size_t prefix_size = is_same_v<Prefix, void> ? 0 : round_to_aligned(sizeof(Prefix), alignof(Prefix));
    static constexpr size_t suffix_size = is_same_v<Suffix, void> ? 0 : round_to_aligned(sizeof(Suffix), alignof(Suffix));

    constexpr bool is_owner(block block) const;

    constexpr block allocate(size_t size);

    constexpr void deallocate(block block);
    constexpr void deallocate_all();

    constexpr void expand(block& block, size_t delta_size);
    constexpr void reallocate(block& block, size_t size);

private:
    static constexpr size_t get_affixed_size(size_t size);
};

template<typename Allocator, typename Prefix, typename Suffix>
constexpr bool affix<Allocator, Prefix, Suffix>::is_owner(block block) const
{
    return Allocator::is_owner(block);
}

template<typename Allocator, typename Prefix, typename Suffix>
constexpr block affix<Allocator, Prefix, Suffix>::allocate(size_t size)
{
    const size_t aligned_size = round_to_aligned(size);

    block block = Allocator::allocate(get_affixed_size(aligned_size));

    if constexpr (!is_same_v<Prefix, void>)
    {
        ::new (reinterpret_cast<Prefix*>(block.pointer))();

        block.pointer += prefix_size;
    }

    if constexpr (!is_same_v<Suffix, void>)
    {
        ::new (reinterpret_cast<Suffix*>(block.pointer + aligned_size))();
    }

    return {block.pointer, size};
}

template<typename Allocator, typename Prefix, typename Suffix>
constexpr block affix<Allocator, Prefix, Suffix>::allocate_all()
{
    block block = Allocator::allocate_all();

    if constexpr (!is_same_v<Prefix, void>)
    {
        ::new (reinterpret_cast<Prefix*>(block.pointer))();

        block.pointer += prefix_size;
    }

    if constexpr (!is_same_v<Suffix, void>)
    {
        ::new (reinterpret_cast<Suffix*>(block.pointer + block.size - suffix_size))();
    }

    return block;
}

template<typename Allocator, typename Prefix, typename Suffix>
constexpr void affix<Allocator, Prefix, Suffix>::deallocate(block block)
{
    return Allocator::deallocate(block);
}

template<typename Allocator, typename Prefix, typename Suffix>
constexpr void affix<Allocator, Prefix, Suffix>::deallocate_all()
{
    return Allocator::deallocate_all();
}

template<typename Allocator, typename Prefix, typename Suffix>
constexpr void affix<Allocator, Prefix, Suffix>::expand(block& block, size_t delta_size)
{
    block internal_block{block.pointer - prefix_size};
    
    Allocator::expand(block, size);

    // TODO Prefix & Suffix
}

template<typename Allocator, typename Prefix, typename Suffix>
constexpr void affix<Allocator, Prefix, Suffix>::reallocate(block& block, size_t size)
{
}

template<typename Allocator, typename Prefix, typename Suffix>
constexpr size_t affix<Allocator, Prefix, Suffix>::get_affixed_size(size_t size)
{
    if constexpr (!is_same_v<Prefix, void>)
    {
        size += round_to_aligned(sizeof(Prefix), alignof(Prefix));
    }

    if constexpr (!is_same_v<Suffix, void>)
    {
        size += round_to_aligned(sizeof(Suffix), alignof(Suffix));
    }

    return size;
}

} // namespace nos::memory::allocator
