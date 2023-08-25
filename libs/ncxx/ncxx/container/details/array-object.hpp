#pragma once

#include <ncxx/container/details/array-base.hpp>
#include <ncxx/memory/construct-at.hpp>
#include <ncxx/type-trait/is-copy-assignable.hpp>
#include <ncxx/type-trait/is-copy-constructible.hpp>
#include <ncxx/type-trait/is-move-assignable.hpp>
#include <ncxx/type-trait/is-move-constructible.hpp>
#include <ncxx/utility/forward.hpp>
#include <ncxx/utility/move.hpp>
#include <ncxx/utility/swap.hpp>

namespace NOS::Details {

// Base class for non-trivial T's
template<typename T, typename TAllocator, typename TSize>
class ArrayObject : public ArrayBase<T, TAllocator, TSize>
{
    using Base = ArrayBase<T, TAllocator, TSize>;
    using typename Base::DataSizeType;

public:
    using typename Base::AllocatorType;

    using typename Base::SizeType;
    using typename Base::ValueType;

    using typename Base::ConstPointer;
    using typename Base::Pointer;

    using typename Base::ConstReference;
    using typename Base::Reference;

public:
    constexpr ArrayObject() = default;
    constexpr ArrayObject(size_t initialSize);
    constexpr ~ArrayObject();

public:
    using Base::capacity;
    using Base::isEmpty;
    using Base::size;

    using Base::first;
    using Base::last;

public:
    constexpr void prepend(ConstReference value);
    constexpr void prepend(T&& value);

    constexpr void append(ConstReference value);
    constexpr void append(T&& value);

    template<typename... TArgs>
    constexpr Reference emplaceFirst(TArgs&&... args);

    template<typename... TArgs>
    constexpr Reference emplaceLast(TArgs&&... args);

    constexpr void removeAt(size_t index);
    constexpr void removeAtSwapLast(size_t index);

    constexpr void removeOne(ConstReference value);
    constexpr void removeOneSwapLast(ConstReference value);

    constexpr void removeFirst();
    constexpr void removeFirstSwapLast();

    constexpr void removeLast();

    constexpr size_t indexOf(ConstReference value) const;

    constexpr void reserve(size_t size);
    constexpr void resize(size_t size);
    constexpr void clear();
    constexpr void free();

protected:
    static void construct(T* to, T* from);
    static void take(T* to, T* from);
    static void destroyRange(T* begin, T* end);

    constexpr void grow(size_t minCapacity, size_t offset = 0);
};

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayObject<T, TAllocator, TSize>::ArrayObject(size_t initialSize)
{
    resize(initialSize);
}

template<typename T, typename TAllocator, typename TSize>
constexpr ArrayObject<T, TAllocator, TSize>::~ArrayObject()
{
    clear();

    TAllocator::deallocate(Memory::Block{Base::_buffer, Base::_size * sizeof(T)});
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::prepend(ConstReference value)
{
    grow(Base::size() + 1, 1);

    Memory::constructAt(static_cast<T*>(Base::_buffer), value);

    ++Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::prepend(T&& value)
{
    grow(Base::size() + 1, 1);

    Memory::constructAt(static_cast<T*>(Base::_buffer), move(value));

    ++Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::append(ConstReference value)
{
    grow(Base::size() + 1);

    Memory::constructAt(static_cast<T*>(Base::_buffer) + Base::_size, value);

    ++Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::append(T&& value)
{
    grow(Base::size() + 1);

    Memory::constructAt(static_cast<T*>(Base::_buffer) + Base::_size, move(value));

    ++Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
template<typename... TArgs>
constexpr ArrayObject<T, TAllocator, TSize>::Reference ArrayObject<T, TAllocator, TSize>::emplaceFirst(TArgs&&... args)
{
    grow(Base::size() + 1, 1);

    Memory::constructAt(static_cast<T*>(Base::_buffer), forward<TArgs>(args)...);

    ++Base::_size;

    return Base::first();
}

template<typename T, typename TAllocator, typename TSize>
template<typename... TArgs>
constexpr ArrayObject<T, TAllocator, TSize>::Reference ArrayObject<T, TAllocator, TSize>::emplaceLast(TArgs&&... args)
{
    grow(Base::size() + 1);

    Memory::constructAt(static_cast<T*>(Base::_buffer) + Base::_size, forward<TArgs>(args)...);

    ++Base::_size;

    return Base::last();
}
template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::removeAt(size_t index)
{
    NOS_ASSERT(index < size());

    for (size_t i = index; i < size() - 1; ++i)
    {
        take(&(*this)[i], &(*this)[i + 1]);
    }

    Memory::destroyAt(&last());

    --Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::removeAtSwapLast(size_t index)
{
    NOS_ASSERT(index < size());

    swap((*this)[index], last());

    removeLast();
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::removeOne(ConstReference value)
{
    const size_t index = indexOf(value);

    if (index < size())
    {
        removeAt(index);
    }
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::removeOneSwapLast(ConstReference value)
{
    const size_t index = indexOf(value);

    if (index < size())
    {
        removeAtSwapLast(index);
    }
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::removeFirst()
{
    removeAt(0);
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::removeFirstSwapLast()
{
    if (size() >= 2)
    {
        swap(first(), last());
    }

    removeLast();
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::removeLast()
{
    NOS_ASSERT(!isEmpty());

    Memory::destroyAt(&last());

    --Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr size_t ArrayObject<T, TAllocator, TSize>::indexOf(ConstReference value) const
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
constexpr void ArrayObject<T, TAllocator, TSize>::reserve(size_t size)
{
    return grow(size);
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::resize(size_t newSize)
{
    if (newSize < size())
    {
        for (size_t i = newSize; i < size(); ++i)
        {
            Memory::destroyAt(&(*this)[i]);
        }
    }
    else if (newSize > size())
    {
        grow(newSize);

        for (size_t i = newSize; i < size(); ++i)
        {
            Memory::constructAt(static_cast<T*>(Base::_buffer) + i);
        }
    }

    Base::_size = static_cast<DataSizeType>(newSize);
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::clear()
{
    destroyRange(reinterpret_cast<T*>(Base::_buffer),
                 reinterpret_cast<T*>(reinterpret_cast<u8_t*>(Base::_buffer) + size() * sizeof(T)));

    Base::_size = 0;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::free()
{
    clear();

    Memory::Block block{.pointer = Base::_buffer, .size = capacity() * sizeof(T)};
    AllocatorType::deallocate(block);

    Base::_capacity = 0;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::grow(size_t minCapacity, size_t offset)
{
    if (minCapacity <= Base::capacity())
    {
        if (offset > 0)
        {
            for (size_t i = Base::_size - 1; i-- > 0;)
            {
                T* from = reinterpret_cast<T*>(reinterpret_cast<u8_t*>(Base::_buffer) + i * sizeof(T));
                T* to = reinterpret_cast<T*>(reinterpret_cast<u8_t*>(Base::_buffer) + (i + offset) * sizeof(T));

                construct(to, from);
            }
        }
        return;
    }

    Memory::Block newBlock = AllocatorType::allocate(Base::getNextCapacity(minCapacity) * sizeof(T));

    NOS_ASSERT(newBlock != Memory::nullblk);

    Memory::Block oldBlock = {Base::_buffer, Base::_capacity * sizeof(T)};

    for (size_t i = 0; i < Base::_size; ++i)
    {
        T* from = reinterpret_cast<T*>(reinterpret_cast<u8_t*>(oldBlock.pointer) + i * sizeof(T));
        T* to = reinterpret_cast<T*>(reinterpret_cast<u8_t*>(newBlock.pointer) + (i + offset) * sizeof(T));

        construct(to, from);
    }

    NOS_ASSERT(newBlock != Memory::nullblk);

    if (!Base::isInplaceBuffer())
    {
        destroyRange(reinterpret_cast<T*>(oldBlock.pointer),
                     reinterpret_cast<T*>(reinterpret_cast<u8_t*>(oldBlock.pointer) + size() * sizeof(T)));
        AllocatorType::deallocate(oldBlock);
    }

    Base::_buffer = newBlock.pointer;
    Base::_capacity = static_cast<DataSizeType>(newBlock.size / sizeof(T));
}

template<typename T, typename TAllocator, typename TSize>
void ArrayObject<T, TAllocator, TSize>::construct(T* to, T* from)
{
    static_assert(IsCopyConstructibleV<T> || IsMoveConstructibleV<T>);

    if constexpr (IsMoveConstructibleV<T>)
    {
        Memory::constructAt(to, move(*from));
    }
    else if constexpr (IsCopyConstructibleV<T>)
    {
        Memory::constructAt(to, *from);
    }
}

template<typename T, typename TAllocator, typename TSize>
void ArrayObject<T, TAllocator, TSize>::take(T* to, T* from)
{
    static_assert(IsCopyAssignableV<T> || IsMoveAssignableV<T>);

    if constexpr (IsMoveAssignableV<T>)
    {
        *to = move(*from);
    }
    else if constexpr (IsCopyAssignableV<T>)
    {
        *to = *from;
    }
}

template<typename T, typename TAllocator, typename TSize>
void ArrayObject<T, TAllocator, TSize>::destroyRange(T* begin, T* end)
{
    for (T* it = begin; it != end; ++it)
    {
        Memory::destroyAt(it);
    }
}

} // namespace NOS::Details
