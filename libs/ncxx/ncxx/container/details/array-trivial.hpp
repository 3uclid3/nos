#pragma once

#include <ncxx/container/details/array-base.hpp>
#include <ncxx/container/details/array-param-type.hpp>
#include <ncxx/utility/swap.hpp>

namespace NOS::Details {

// Base class for trivial T's
template<typename T, typename TAllocator, typename TSize>
class ArrayTrivial : public ArrayBase<T, TAllocator, TSize>
{
    using Base = ArrayBase<T, TAllocator, TSize>;

public:
    using typename Base::AllocatorType;

    using typename Base::SizeType;
    using typename Base::ValueType;
    using ValueParamType = Details::ArrayParamTypeT<T>;

    using typename Base::ConstPointer;
    using typename Base::Pointer;

    using typename Base::ConstReference;
    using typename Base::Reference;

public:
    constexpr ArrayTrivial() = default;
    constexpr ArrayTrivial(size_t initialSize);

public:
    using Base::capacity;
    using Base::isEmpty;
    using Base::size;

    using Base::first;
    using Base::last;

public:
    constexpr Reference emplaceFirst(ValueParamType value);
    constexpr Reference emplaceLast(ValueParamType value);

    constexpr void prepend(ValueParamType value);
    constexpr void append(ValueParamType value);

    constexpr void removeAt(size_t index);
    constexpr void removeAtSwapLast(size_t index);

    constexpr void removeOne(ValueParamType value);
    constexpr void removeOneSwapLast(ValueParamType value);

    constexpr void removeFirst();
    constexpr void removeFirstSwapLast();

    constexpr void removeLast();

    constexpr size_t indexOf(ValueParamType value) const;

    constexpr void resize(size_t size);
    constexpr void resize(size_t size, ValueParamType value);
    constexpr void clear();

protected:
    constexpr void grow(size_t size, size_t offset = 0);
};

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayTrivial<T, TAllocator, TSize>::ArrayTrivial(size_t initialSize)
{
    grow(initialSize);

    Base::_size = initialSize;
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayTrivial<T, TAllocator, TSize>::Reference ArrayTrivial<T, TAllocator, TSize>::emplaceFirst(ValueParamType value)
{
    prepend(value);
    return first();
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayTrivial<T, TAllocator, TSize>::Reference ArrayTrivial<T, TAllocator, TSize>::emplaceLast(ValueParamType value)
{
    append(value);
    return last();
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::prepend(ValueParamType value)
{
    grow(size() + 1, 1);

    Memory::copy(Memory::Block{Base::_buffer, Base::capacity()}, Memory::Block{&value, sizeof(T)});

    ++Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::append(ValueParamType value)
{
    grow(size() + 1);

    Memory::copy(Memory::Block{reinterpret_cast<u8_t*>(Base::_buffer) + Base::_size * sizeof(T), sizeof(T)},
                 Memory::Block{&value, sizeof(T)});

    ++Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::removeAt(size_t index)
{
    NOS_ASSERT(index < size());

    const size_t sizeToMove = (size() - index - 1) * sizeof(T);

    Memory::move(Memory::Block{reinterpret_cast<u8_t*>(Base::_buffer) + index * sizeof(T), sizeToMove},
                 Memory::Block{reinterpret_cast<u8_t*>(Base::_buffer) + (index + 1) * sizeof(T), sizeToMove});

    --Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::removeAtSwapLast(size_t index)
{
    NOS_ASSERT(index < size());
    swap((*this)[index], last());
    removeLast();
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::removeOne(ValueParamType value)
{
    const size_t index = indexOf(value);

    if (index < size())
    {
        removeAt(index);
    }
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::removeOneSwapLast(ValueParamType value)
{
    const size_t index = indexOf(value);

    if (index < size())
    {
        removeAtSwapLast(index);
    }
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::removeFirst()
{
    removeAt(0);
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::removeFirstSwapLast()
{
    if (size() >= 2)
    {
        swap(first(), last());
    }
    removeLast();
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::removeLast()
{
    NOS_ASSERT(!isEmpty());
    --Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr size_t ArrayTrivial<T, TAllocator, TSize>::indexOf(ValueParamType value) const
{
    for (size_t i = 0; i < Base::_size; ++i)
    {
        if ((*this)[i] == value)
        {
            return i;
        }
    }
    return Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::resize(size_t size)
{
    grow(size);

    Base::_size = size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::resize(size_t size, ValueParamType value)
{
    const size_t previousSize = Base::_size;

    resize(size);

    for (size_t i = previousSize; i < size; ++i)
    {
        (*this)[i] = value;
    }
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::clear()
{
    Base::_size = 0;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::grow(size_t minCapacity, size_t offset)
{
    if (minCapacity <= capacity())
    {
        if (offset > 0)
        {
            Memory::move(Memory::Block{reinterpret_cast<u8_t*>(Base::_buffer) + offset * sizeof(T), Base::_size * sizeof(T)},
                         Memory::Block{Base::_buffer, Base::_size * sizeof(T)});
        }
        return;
    }

    Memory::Block newBlock = AllocatorType::allocate(Base::getNextCapacity(minCapacity) * sizeof(T));
    Memory::Block oldBlock = {Base::_buffer, Base::_capacity * sizeof(T)};

    NOS_ASSERT(newBlock != Memory::nullblk);

    // copy existing data
    Memory::copy(Memory::Block{reinterpret_cast<u8_t*>(newBlock.pointer) + offset * sizeof(T), newBlock.size - (offset * sizeof(T))},
                 oldBlock);

    if (!Base::isInplaceBuffer())
    {
        AllocatorType::deallocate(oldBlock);
    }

    Base::_buffer = newBlock.pointer;
    Base::_capacity = newBlock.size / sizeof(T);
}

} // namespace NOS::Details
