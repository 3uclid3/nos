#pragma once

#include <ncxx/container/details/array-data.hpp>
#include <ncxx/debug/assert.hpp>
#include <ncxx/iterator/reverse-iterator.hpp>
#include <ncxx/memory/block.hpp>
#include <ncxx/memory/voidify.hpp>

namespace NOS::Details {

// we inherit from our allocator to ensure we're properly aligned even for size 0 allocator class
template<typename T, typename TAllocator, typename TSize>
class ArrayRawBase : public ArrayData<TSize>, protected TAllocator
{
public:
    using AllocatorType = TAllocator;
    using SizeType = size_t;
    using ValueType = T;
};

template<typename T, typename TAllocator, typename TSize>
class ArrayBase : public ArrayRawBase<T, TAllocator, TSize>
{
    using Base = ArrayRawBase<T, TAllocator, TSize>;

public:
    using AllocatorType = Base::AllocatorType;

    using SizeType = Base::SizeType;
    using ValueType = Base::ValueType;

    using ConstPointer = const T*;
    using Pointer = T*;

    using ConstReference = const T&;
    using Reference = T&;

    using ConstIterator = const T*;
    using Iterator = T*;

    using ConstReverseIterator = NOS::ReverseIterator<ConstIterator>;
    using ReverseIterator = NOS::ReverseIterator<Iterator>;

public:
    using Base::capacity;
    using Base::isEmpty;
    using Base::size;

public:
    constexpr ConstReference operator[](size_t index) const;
    constexpr Reference operator[](size_t index);

public:
    constexpr ConstReference first() const;
    constexpr Reference first();

    constexpr ConstReference last() const;
    constexpr Reference last();

    constexpr ConstPointer data() const;
    constexpr Pointer data();

public:
    constexpr ConstIterator begin() const;
    constexpr ConstIterator end() const;

    constexpr ConstIterator cbegin() const;
    constexpr ConstIterator cend() const;

    constexpr Iterator begin();
    constexpr Iterator end();

    constexpr ConstReverseIterator rbegin() const;
    constexpr ConstReverseIterator rend() const;

    constexpr ConstReverseIterator rcbegin() const;
    constexpr ConstReverseIterator rcend() const;

    constexpr ReverseIterator rbegin();
    constexpr ReverseIterator rend();

protected:
    // Helper to figure out the offset of the first element
    constexpr uintptr_t getOffsetOfFirstInplace() const;
    constexpr void* getAddressOfFirstInplace() const;

    constexpr bool isInplaceBuffer() const;

    constexpr bool isValidIterator(ConstIterator it) const;
};

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::ConstReference ArrayBase<T, TAllocator, TSize>::operator[](size_t index) const
{
    NOS_ASSERT(index < size());

    return data()[index];
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::Reference ArrayBase<T, TAllocator, TSize>::operator[](size_t index)
{
    NOS_ASSERT(index < size());

    return data()[index];
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::ConstReference ArrayBase<T, TAllocator, TSize>::first() const
{
    return (*this)[0];
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::Reference ArrayBase<T, TAllocator, TSize>::first()
{
    return (*this)[0];
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::ConstReference ArrayBase<T, TAllocator, TSize>::last() const
{
    NOS_ASSERT(!isEmpty());
    return (*this)[size() - 1];
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::Reference ArrayBase<T, TAllocator, TSize>::last()
{
    NOS_ASSERT(!isEmpty());
    return (*this)[size() - 1];
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::ConstPointer ArrayBase<T, TAllocator, TSize>::data() const
{
    return reinterpret_cast<ConstPointer>(Base::_buffer);
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::Pointer ArrayBase<T, TAllocator, TSize>::data()
{
    return reinterpret_cast<Pointer>(Base::_buffer);
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::ConstIterator ArrayBase<T, TAllocator, TSize>::begin() const
{
    return ConstIterator{data()};
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::ConstIterator ArrayBase<T, TAllocator, TSize>::end() const
{
    return ConstIterator{data() + size()};
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::ConstIterator ArrayBase<T, TAllocator, TSize>::cbegin() const
{
    return begin();
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::ConstIterator ArrayBase<T, TAllocator, TSize>::cend() const
{
    return end();
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::Iterator ArrayBase<T, TAllocator, TSize>::begin()
{
    return Iterator{data()};
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayBase<T, TAllocator, TSize>::Iterator ArrayBase<T, TAllocator, TSize>::end()
{
    return Iterator{data() + size()};
}

template<typename T, typename TAllocator, typename TSize>
constexpr uintptr_t ArrayBase<T, TAllocator, TSize>::getOffsetOfFirstInplace() const
{
    struct Array
    {
        alignas(Base) byte_t base[sizeof(Base)];
        alignas(T) byte_t first[sizeof(T)];
    };

    return offsetof(Array, first);
}

template<typename T, typename TAllocator, typename TSize>
constexpr void* ArrayBase<T, TAllocator, TSize>::getAddressOfFirstInplace() const
{
    /// Find the address of the first element. For this pointer math to be valid
    /// with inplace of 0 for T with lots of alignment, it's important that
    /// ArrayStorage is properly-aligned even for inplace of 0.
    return const_cast<void*>(reinterpret_cast<const void*>(reinterpret_cast<const byte_t*>(this) + getOffsetOfFirstInplace()));
}

template<typename T, typename TAllocator, typename TSize>
constexpr bool ArrayBase<T, TAllocator, TSize>::isInplaceBuffer() const
{
    return Base::_buffer == getAddressOfFirstInplace();
}

template<typename T, typename TAllocator, typename TSize>
constexpr bool ArrayBase<T, TAllocator, TSize>::isValidIterator(ConstIterator it) const
{
    const u8_t* buffer = static_cast<const u8_t*>(Base::_buffer);
    const u8_t* bufferEnd = buffer + sizeof(T) * size();

    const void* voidPtr = it;
    const u8_t* pointer = static_cast<const u8_t*>(voidPtr);

    return pointer >= buffer && pointer < bufferEnd;
}

} // namespace NOS::Details
