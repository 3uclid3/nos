#pragma once

#include <ncxx/container/details/array-base.hpp>
#include <ncxx/type-trait/is-copy-assignable.hpp>
#include <ncxx/type-trait/is-copy-constructible.hpp>
#include <ncxx/type-trait/is-move-assignable.hpp>
#include <ncxx/type-trait/is-move-constructible.hpp>
#include <ncxx/utility/forward.hpp>
#include <ncxx/utility/move.hpp>

namespace NOS::Details {

// Base class for non-trivial T's
template<typename T, typename TAllocator, typename TSize>
class ArrayObject : public ArrayBase<T, TAllocator, TSize>
{
    using Base = ArrayBase<T, TAllocator, TSize>;

public:
    using typename Base::AllocatorType;

    using typename Base::SizeType;
    using typename Base::ValueType;

    using typename Base::ConstPointer;
    using typename Base::Pointer;

    using typename Base::ConstReference;
    using typename Base::Reference;

public:
    constexpr void prepend(ConstReference value);
    constexpr void prepend(T&& value);

    constexpr void append(ConstReference value);
    constexpr void append(T&& value);

    template<typename... TArgs>
    constexpr Reference emplaceFirst(TArgs&&... args);

    template<typename... TArgs>
    constexpr Reference emplaceLast(TArgs&&... args);

protected:
    static void destroyRange(T* begin, T* end);

    static void construct(T* to, T* from);

    constexpr void grow(size_t minCapacity, size_t offset = 0);
};

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::prepend(ConstReference value)
{
    grow(Base::size() + 1, 1);

    ::new (Base::_buffer) T(value);

    ++Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::prepend(T&& value)
{
    grow(Base::size() + 1, 1);

    ::new (Base::_buffer) T(move(value));

    ++Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::append(ConstReference value)
{
    grow(Base::size() + 1);

    ::new (reinterpret_cast<u8_t*>(Base::_buffer) + Base::_size * sizeof(T)) T(value);

    ++Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ArrayObject<T, TAllocator, TSize>::append(T&& value)
{
    grow(Base::size() + 1);

    ::new (reinterpret_cast<u8_t*>(Base::_buffer) + Base::_size * sizeof(T)) T(move(value));

    ++Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
template<typename... TArgs>
constexpr ArrayObject<T, TAllocator, TSize>::Reference ArrayObject<T, TAllocator, TSize>::emplaceFirst(TArgs&&... args)
{
    grow(Base::size() + 1, 1);

    ::new (Base::_buffer) T(forward<TArgs>(args)...);

    ++Base::_size;

    return Base::first();
}

template<typename T, typename TAllocator, typename TSize>
template<typename... TArgs>
constexpr ArrayObject<T, TAllocator, TSize>::Reference ArrayObject<T, TAllocator, TSize>::emplaceLast(TArgs&&... args)
{
    grow(Base::size() + 1);

    ::new (reinterpret_cast<u8_t*>(Base::_buffer) + Base::_size * sizeof(T)) T(forward<TArgs>(args)...);

    ++Base::_size;

    return Base::last();
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
        AllocatorType::deallocate(oldBlock);
    }

    Base::_buffer = newBlock.pointer;
    Base::_capacity = newBlock.size / sizeof(T);
}

template<typename T, typename TAllocator, typename TSize>
void ArrayObject<T, TAllocator, TSize>::construct(T* to, T* from)
{
    static_assert(IsCopyConstructibleV<T> || IsMoveConstructibleV<T>);

    if constexpr (IsMoveConstructibleV<T>)
    {
        ::new (to) T(move(*from));
    }
    else if constexpr (IsCopyConstructibleV<T>)
    {
        ::new (to) T(*from);
    }
}

} // namespace NOS::Details
