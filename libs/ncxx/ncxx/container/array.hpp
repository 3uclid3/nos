#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/memory/block.hpp>
#include <ncxx/type-trait/conditional.hpp>

namespace NOS {

template<class T>
using ArraySizeTypeT = ConditionalT<sizeof(T) < 4 && sizeof(void*) >= 8, u64_t, u32_t>;

namespace Details {

// we inherit from our allocator to ensure we're properly aligned even for size 0 allocator class
template<typename T, typename TAllocator>
class ArrayBase : private TAllocator
{
public:
    using AllocatorType = TAllocator;

public:
    constexpr ArrayBase() = default;

protected:
    void* _pointer;
    ArraySizeTypeT<T> _size{0};
    ArraySizeTypeT<T> _capacity{0};
};

/// Helper to figure out the offset of the first element
template<typename T, typename TAllocator>
struct ArrayAlignmentAndSize
{
    alignas(ArrayBase<T, TAllocator>) byte_t base[sizeof(ArrayBase<T, TAllocator>)];
    alignas(T) byte_t first[sizeof(T)];
};

template<typename T, typename TAllocator>
constexpr auto getArrayOffsetOfFirst()
{
    using AlignmentAndSize = ArrayAlignmentAndSize<T, TAllocator>;
    return offsetof(AlignmentAndSize, first);
}

struct DefaultAllocator{};

} // namespace Details

template<typename T, typename TAllocator = Details::DefaultAllocator>
class Array : public Details::ArrayBase<T, TAllocator>
{
    using Base = Details::ArrayBase<T, TAllocator>;

public:
    using typename Base::AllocatorType;

    constexpr bool isAllocated() const;

public:
    constexpr void add(const T& value);

    // protected:
    constexpr void* getAddressOfFirst() const;

private:
    constexpr void growIfNecessary(size_t requiredSize);
};

template<typename T, ArraySizeTypeT<T> TSize, typename TAllocator>
class InplaceArray : public Array<T, TAllocator>
{
    using Base = Array<T, TAllocator>;

public:
    constexpr InplaceArray();

private:
    alignas(T) byte_t _inplace[TSize * sizeof(T)];
};

template<typename T, typename TAllocator>
constexpr bool Array<T, TAllocator>::isAllocated() const
{
    return Base::_pointer != getAddressOfFirst();
}

template<typename T, typename TAllocator>
constexpr void Array<T, TAllocator>::add(const T& value)
{
    const auto newSize = Base::_size + 1;

    growIfNecessary(newSize);

    Base::_pointer[Base::_size] = value;

    Base::_size = newSize;
}

template<typename T, typename TAllocator>
constexpr void* Array<T, TAllocator>::getAddressOfFirst() const
{
    /// Find the address of the first element. For this pointer math to be valid
    /// with small-size of 0 for T with lots of alignment, it's important that
    /// ArrayStorage is properly-aligned even for small-size of 0.
    return const_cast<void*>(reinterpret_cast<const void*>(reinterpret_cast<const byte_t*>(this) + Details::getArrayOffsetOfFirst<T, TAllocator>()));
}

template<typename T, typename TAllocator>
constexpr void Array<T, TAllocator>::growIfNecessary(size_t requiredSize)
{
    if (requiredSize <= Base::_capacity)
    {
        return;
    }

    const auto newCapacity = Base::_capacity * 2;

    Memory::Block block = AllocatorType::allocate(newCapacity);

    T* oldPtr = reinterpret_cast<T*>(Base::_pointer);
    T* newPtr = reinterpret_cast<T*>(block.pointer);
    for (auto i = 0; i < Base::_size; ++i)
    {
        newPtr[i] = oldPtr[i];
    }

    if (isAllocated())
    {
        AllocatorType::deallocate(Memory::Block{Base::_pointer, Base::_capacity});
    }

    Base::_pointer = block.pointer;
    Base::_capacity = block.size;
}

template<typename T, ArraySizeTypeT<T> TSize, typename TAllocator>
constexpr InplaceArray<T, TSize, TAllocator>::InplaceArray()
{
    Base::_pointer = _inplace;
    Base::_capacity = TSize;
}

} // namespace NOS
