#pragma once

#include <ncxx/algorithm/clamp.hpp>
#include <ncxx/basic-types.hpp>
#include <ncxx/container/details/array-base-type.hpp>
#include <ncxx/container/details/array-param-type.hpp>
#include <ncxx/container/details/array-size-type.hpp>
#include <ncxx/debug/assert.hpp>
#include <ncxx/iterator/reverse-iterator.hpp>
#include <ncxx/type-trait/conditional.hpp>
#include <ncxx/type-trait/integral-constant.hpp>
#include <ncxx/utility/initializer-list.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

namespace NOS {

namespace Details {

struct DefaultAllocator
{};

} // namespace Details

template<typename T, typename TAllocator = Details::DefaultAllocator, typename TSize = Details::ArraySizeTypeT<T>>
class Array : public Details::ArrayBaseTypeT<T, TAllocator, TSize>
{
    using Base = Details::ArrayBaseTypeT<T, TAllocator, TSize>;

public:
    using typename Base::AllocatorType;

    using ValueType = T;
    using ValueParamType = Details::ArrayParamTypeT<T>;

    using ConstPointer = const T*;
    using Pointer = T*;

    using ConstReference = const T&;
    using Reference = T&;

    class ConstIterator
    {
    public:
        constexpr ConstIterator() = default;
        constexpr ConstIterator(ConstPointer pointer);

        constexpr bool operator==(const ConstIterator& other) const = default;

        constexpr ConstReference operator*() const;
        constexpr ConstPointer operator->() const;

        constexpr ConstIterator& operator++();
        constexpr ConstIterator operator++(int);

    private:
        ConstPointer _pointer{};
    };

    class Iterator
    {
    public:
        constexpr Iterator() = default;
        constexpr Iterator(Pointer pointer);

        constexpr bool operator==(const Iterator& other) const = default;

        constexpr Reference operator*() const;
        constexpr Pointer operator->() const;

        constexpr Iterator& operator++();
        constexpr Iterator operator++(int);

    private:
        Pointer _pointer{};
    };

    using ConstReverseIterator = NOS::ReverseIterator<ConstIterator>;
    using ReverseIterator = NOS::ReverseIterator<Iterator>;

public:
    constexpr Array() = default;
    constexpr Array(size_t initialSize);
    constexpr Array(size_t initialSize, const T& initialValue);

    constexpr Array(InitializerList<T> ilist);

    template<typename TIterator>
    constexpr Array(TIterator begin, TIterator end);

    constexpr Array(const Array& other);
    constexpr Array(Array&& other);

public:
    constexpr bool operator==(const Array& other) const;

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

public:
    constexpr bool isEmpty() const;
    constexpr size_t size() const;
    constexpr size_t maximumSize() const;
    constexpr size_t capacity() const;

    constexpr void reserve(size_t size);

public:
    template<typename... TArgs>
    constexpr Reference emplace(TArgs&&... args);

    constexpr void prepend(ValueParamType value);
    constexpr void append(ValueParamType value);

    constexpr void insert(ConstIterator before, ValueParamType value);
    constexpr void insert(ConstIterator before, T&& value);
    constexpr void insert(ConstIterator before, InitializerList<T> ilist);

    template<typename TIterator>
    constexpr void insert(ConstIterator before, TIterator begin, TIterator end);

    constexpr void removeAt(size_t index);
    constexpr void removeAtSwapLast(size_t index);

    constexpr void removeAt(ConstIterator it);
    constexpr void removeAtSwapLast(ConstIterator it);

    constexpr void removeOne(ValueParamType value);
    constexpr void removeOneSwapLast(ValueParamType value);

    constexpr void removeFirst();
    constexpr void removeFirstSwapLast();

    constexpr void removeLast();

    constexpr void resize(size_t size);
    constexpr void resize(size_t size, ConstReference value);
    constexpr void clear();
};

// template<typename T, ArraySizeTypeT<T> TSize, typename TAllocator>
// class EmbeddedArray : public Array<T, TAllocator>
//{
//     using Base = Array<T, TAllocator>;
//
// public:
//     constexpr EmbeddedArray();
//
// private:
//     alignas(T) byte_t _inplace[TSize * sizeof(T)];
// };

// ---------------------------------------------------------------------------------------------

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstIterator::ConstIterator(ConstPointer pointer)
    : _pointer(pointer)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstReference Array<T, TAllocator, TSize>::ConstIterator::operator*() const
{
    return *_pointer;
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstPointer Array<T, TAllocator, TSize>::ConstIterator::operator->() const
{
    return _pointer;
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstIterator& Array<T, TAllocator, TSize>::ConstIterator::operator++()
{
    ++_pointer;
    return *this;
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstIterator Array<T, TAllocator, TSize>::ConstIterator::operator++(int)
{
    auto it = *this;
    ++_pointer;
    return it;
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Iterator::Iterator(Pointer pointer)
    : _pointer(pointer)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Reference Array<T, TAllocator, TSize>::Iterator::operator*() const
{
    return *_pointer;
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Pointer Array<T, TAllocator, TSize>::Iterator::operator->() const
{
    return _pointer;
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Iterator& Array<T, TAllocator, TSize>::Iterator::operator++()
{
    ++_pointer;
    return *this;
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Iterator Array<T, TAllocator, TSize>::Iterator::operator++(int)
{
    auto it = *this;
    ++_pointer;
    return it;
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Array(size_t initialSize)
{
    resize(initialSize);
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Array(size_t initialSize, const T& initialValue)
{
    resize(initialSize, initialValue);
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Array(InitializerList<T> ilist)
{
    insert(end(), ilist);
}

template<typename T, typename TAllocator, typename TSize>
template<typename TIterator>
constexpr Array<T, TAllocator, TSize>::Array(TIterator begin, TIterator end)
{
    insert(end(), begin, end);
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Array(const Array& other)
{
    copyFrom(other);
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Array(Array&& other)
{
    moveFrom(other);
}

template<typename T, typename TAllocator, typename TSize>
constexpr bool Array<T, TAllocator, TSize>::operator==(const Array& other) const
{
    return false;
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstIterator Array<T, TAllocator, TSize>::begin() const
{
    return ConstIterator{data()};
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstIterator Array<T, TAllocator, TSize>::end() const
{
    return ConstIterator{data() + size()};
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstIterator Array<T, TAllocator, TSize>::cbegin() const
{
    return ConstIterator{data()};
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstIterator Array<T, TAllocator, TSize>::cend() const
{
    return ConstIterator{data() + size()};
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Iterator Array<T, TAllocator, TSize>::begin()
{
    return Iterator{data()};
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Iterator Array<T, TAllocator, TSize>::end()
{
    return Iterator{data() + size()};
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstReverseIterator Array<T, TAllocator, TSize>::rbegin() const
{
    return isEmpty() ? ConstReverseIterator{} : ConstReverseIterator{data() + size() - 1};
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstReverseIterator Array<T, TAllocator, TSize>::rend() const
{
    return isEmpty() ? ConstReverseIterator{} : ConstReverseIterator{data() - 1};
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstReverseIterator Array<T, TAllocator, TSize>::rcbegin() const
{
    return rbegin();
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstReverseIterator Array<T, TAllocator, TSize>::rcend() const
{
    return rend();
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ReverseIterator Array<T, TAllocator, TSize>::rbegin()
{
    return isEmpty() ? ReverseIterator{} : ReverseIterator{data() + size() - 1};
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ReverseIterator Array<T, TAllocator, TSize>::rend()
{
    return isEmpty() ? ReverseIterator{} : ReverseIterator{data() - 1};
}

template<typename T, typename TAllocator, typename TSize>
constexpr bool Array<T, TAllocator, TSize>::isEmpty() const
{
    return size() == 0;
}

template<typename T, typename TAllocator, typename TSize>
constexpr size_t Array<T, TAllocator, TSize>::size() const
{
    return Base::_size;
}

template<typename T, typename TAllocator, typename TSize>
constexpr size_t Array<T, TAllocator, TSize>::maximumSize() const
{
    // TODO NumericLimit
    return static_cast<TSize>(-1);
}

template<typename T, typename TAllocator, typename TSize>
constexpr size_t Array<T, TAllocator, TSize>::capacity() const
{
    return Base::_capacity;
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::reserve(size_t size)
{
    if (size > capacity())
    {
        //        grow(size);
    }
}

template<typename T, typename TAllocator, typename TSize>
template<typename... TArgs>
constexpr Array<T, TAllocator, TSize>::Reference Array<T, TAllocator, TSize>::emplace(TArgs&&... args)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::prepend(ValueParamType value)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::append(ValueParamType value)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::insert(ConstIterator before, ValueParamType value)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::insert(ConstIterator before, T&& value)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::insert(ConstIterator before, InitializerList<T> ilist)
{
}

template<typename T, typename TAllocator, typename TSize>
template<typename TIterator>
constexpr void Array<T, TAllocator, TSize>::insert(ConstIterator before, TIterator begin, TIterator end)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::removeAt(size_t index)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::removeAtSwapLast(size_t index)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::removeAt(ConstIterator it)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::removeAtSwapLast(ConstIterator it)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::removeOne(ValueParamType value)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::removeOneSwapLast(ValueParamType value)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::removeFirst()
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::removeFirstSwapLast()
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::removeLast()
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::resize(size_t size)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::resize(size_t size, ConstReference value)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void Array<T, TAllocator, TSize>::clear()
{
}

/*
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
*/
} // namespace NOS

#pragma clang diagnostic pop