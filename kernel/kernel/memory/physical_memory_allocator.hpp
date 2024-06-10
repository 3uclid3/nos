#pragma once

#include <kernel/def.hpp>
#include <kernel/memory/physical_memory.hpp>
#include <nxx/memory/alignment.hpp>
#include <nxx/memory/memory_block.hpp>
#include <nxx/type_trait/macro/declare_has_method.macro.hpp>
#include <nxx/utility/passkey.hpp>

namespace nos {

class physical_memory_allocator
{
public:
    static constexpr size_t alignment = default_alignment;

    bool owns(const memory_block& block) const;
    memory_block allocate(size_t size);
    void deallocate(memory_block& block);

    static void set_physical_memory(passkey<physical_memory>, physical_memory* physical_memory) { _physical_memory = physical_memory; }

private:
    inline static physical_memory* _physical_memory{nullptr};
};

NXX_TYPE_TRAIT_HAS_METHOD(has_set_physical_memory, set_physical_memory, void, physical_memory*);

template<typename AllocatorT>
void set_physical_memory_if_exists(AllocatorT& allocator, physical_memory* memory);

template<typename AllocatorT>
void set_physical_memory_if_exists(AllocatorT& allocator, physical_memory* memory)
{
    if constexpr (has_set_physical_memory<AllocatorT>)
    {
        allocator.set_physical_memory(memory);
    }
}

// Function template to traverse composite allocator and set physical memory
template<typename... AllocatorsT>
void set_physical_memory_for_all(physical_memory* memory, AllocatorsT&... allocators)
{
    (set_physical_memory_if_exists(allocators, memory), ...);
}

} // namespace nos
