#pragma once

#include <algorithm/max.hpp>
#include <memory/block.hpp>
#include <memory/utility.hpp>

namespace NOS::Memory {

template<typename TAllocator, typename TPrefix, typename TSuffix = void>
class AffixAllocator : private TAllocator
{
public:
    using AllocatorType = TAllocator;

    using PrefixType = TPrefix;
    using SuffixType = TSuffix;

    static constexpr alignment_t Alignment = AllocatorType::Alignment;

    static constexpr size_t PrefixSize = IsSameV<TPrefix, void> ? 0 : roundToAlignment(sizeof(Prefix), alignof(Prefix));
    static constexpr size_t SuffixSize = IsSameV<TSuffix, void> ? 0 : roundToAlignment(sizeof(Suffix), alignof(Suffix));

    constexpr bool owns(Block block) const;

    constexpr Block allocate(size_t size);

    constexpr void deallocate(Block block);
    constexpr void deallocateAll();

    constexpr Block expand(Block block, size_t size);
    constexpr Block reallocate(Block block, size_t size);

private:
    static constexpr Prefix* toPrefix(Block block);
    static constexpr Suffix* toSuffix(Block block);

    static constexpr Block addAffixes(Block block);
    static constexpr Block removeAffixes(Block block);
};

template<typename TAllocator, typename TPrefix, typename TSuffix>
constexpr bool AffixAllocator<TAllocator, TPrefix, TSuffix>::owns(Block block) const
{
    return AllocatorType::owns(block);
}

template<typename TAllocator, typename TPrefix, typename TSuffix>
constexpr Block AffixAllocator<TAllocator, TPrefix, TSuffix>::allocate(size_t size)
{
    if (size == 0)
    {
        return nullblk;
    }

    Block block = Allocator::allocate(PrefixSize + size + SuffixSize);

    if (block == nullblk)
    {
        return nullblk;
    }

    if constexpr (PrefixSize > 0)
    {
        new (toPrefix(block)) PrefixType{};
    }

    if constexpr (SuffixSize > 0)
    {
        new (toSuffix(block)) SuffixType{};
    }

    return removeAffixes(block);
}

template<typename TAllocator, typename TPrefix, typename TSuffix>
constexpr void AffixAllocator<TAllocator, TPrefix, TSuffix>::deallocate(Block block)
{
    AllocatorType::deallocate(block);
}

template<typename TAllocator, typename TPrefix, typename TSuffix>
constexpr void AffixAllocator<TAllocator, TPrefix, TSuffix>::deallocateAll()
{
    AllocatorType::deallocateAll();
}

template<typename TAllocator, typename TPrefix, typename TSuffix>
constexpr Block AffixAllocator<TAllocator, TPrefix, TSuffix>::expand(Block block, size_t size)
{
    if (size == 0)
    {
        return block;
    }

    if (block == nullblk)
    {
        return allocate(size);
    }

    Block expandedBlock = Allocator::expand(addAffixes(block), size);

    if (expandedBlock == nullblk)
    {
        return nullblk;
    }

    if constexpr (SuffixSize > 0)
    {
        new (toSuffix(expandedBlock)) SuffixType{};
    }

    return removeAffixes(expandedBlock);
}

template<typename TAllocator, typename TPrefix, typename TSuffix>
constexpr void AffixAllocator<TAllocator, TPrefix, TSuffix>::reallocate(Block block, size_t size)
{
    NOS_UNUSED(block);
    NOS_UNUSED(size);

    NOS_ASSERT(false, "To be implemented");
}

template<typename TAllocator, typename TPrefix, typename TSuffix>
constexpr AffixAllocator<TAllocator, TPrefix, TSuffix>::PrefixType* AffixAllocator<TAllocator, TPrefix, TSuffix>::toPrefix(Block block) const
{
    return static_cast<PrefixType*>(block.pointer);
}

template<typename TAllocator, typename TPrefix, typename TSuffix>
constexpr AffixAllocator<TAllocator, TPrefix, TSuffix>::SuffixType* AffixAllocator<TAllocator, TPrefix, TSuffix>::toSuffix(Block block) const
{
    return reinterpret_cast<SuffixType*>(static_cast<u8_t*>(block.pointer) + block.size - SuffixSize);
}

template<typename TAllocator, typename TPrefix, typename TSuffix>
constexpr Block AffixAllocator<TAllocator, TPrefix, TSuffix>::addAffixes(Block block)
{
    return {static_cast<u8_t*>(block.pointer) - PrefixSize, block.size + PrefixSize + SuffixSize};
}

template<typename TAllocator, typename TPrefix, typename TSuffix>
constexpr Block AffixAllocator<TAllocator, TPrefix, TSuffix>::removeAffixes(Block block)
{
    return {static_cast<u8_t*>(block.pointer) + PrefixSize, block.size - PrefixSize - SuffixSize};
}

} // namespace NOS::Memory
