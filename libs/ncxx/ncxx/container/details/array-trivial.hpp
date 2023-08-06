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
    using typename Base::DataSizeType;

public:
    using typename Base::AllocatorType;

    using typename Base::SizeType;
    using typename Base::ValueType;
    using ValueParamType = Details::ArrayParamTypeT<T>;

    using typename Base::ConstPointer;
    using typename Base::Pointer;

    using typename Base::ConstReference;
    using typename Base::Reference;

    using typename Base::ConstIterator;
    using typename Base::Iterator;

public:
    constexpr ArrayTrivial() = default;
    constexpr ArrayTrivial(size_t initialSize);
    constexpr ~ArrayTrivial();

public:
    using Base::capacity;
    using Base::isEmpty;
    using Base::size;

    using Base::first;
    using Base::last;

    using Base::begin;
    using Base::end;

    using Base::cbegin;
    using Base::cend;

public:
    constexpr Reference emplaceFirst(ValueParamType value);
    constexpr Reference emplaceLast(ValueParamType value);

    constexpr void prepend(ValueParamType value);
    constexpr void append(ValueParamType value);

    constexpr void removeAt(size_t index);
    constexpr void removeAtSwapLast(size_t index);

    constexpr void removeIt(ConstIterator it);
    constexpr void removeItSwapLast(ConstIterator it);

    constexpr void removeOne(ValueParamType value);
    constexpr void removeOneSwapLast(ValueParamType value);

    constexpr void removeFirst();
    constexpr void removeFirstSwapLast();

    constexpr void removeLast();

    constexpr size_t indexOf(ValueParamType value) const;
    constexpr size_t indexOf(ConstIterator it) const;

    constexpr void reserve(size_t size);
    constexpr void resize(size_t size);
    constexpr void resize(size_t size, ValueParamType value);
    constexpr void clear();
    constexpr void free();

protected:
    constexpr void grow(size_t size, size_t offset = 0);
};

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayTrivial<T, TAllocator, TSize>::ArrayTrivial(size_t initialSize)
{
    grow(initialSize);

    Base::_size = static_cast<DataSizeType>(initialSize);
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayTrivial<T, TAllocator, TSize>::~ArrayTrivial()
{
    free();
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
constexpr void ArrayTrivial<T, TAllocator, TSize>::removeIt(ConstIterator it)
{
    return removeAt(indexOf(it));
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::removeItSwapLast(ConstIterator it)
{
    return removeAtSwapLast(indexOf(it));
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
constexpr size_t ArrayTrivial<T, TAllocator, TSize>::indexOf(ConstIterator it) const
{
    NOS_ASSERT(Base::isValidIterator(it));
    return size() - static_cast<size_t>(end() - it);
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::reserve(size_t size)
{
    grow(size);
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayTrivial<T, TAllocator, TSize>::resize(size_t size)
{
    grow(size);

    Base::_size = static_cast<DataSizeType>(size);
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
constexpr void ArrayTrivial<T, TAllocator, TSize>::free()
{
    clear();

    Memory::Block block{.pointer = Base::_buffer, .size = capacity() * sizeof(T)};
    AllocatorType::deallocate(block);

    Base::_capacity = 0;
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
    Base::_capacity = static_cast<DataSizeType>(newBlock.size / sizeof(T));
}

} // namespace NOS::Details
