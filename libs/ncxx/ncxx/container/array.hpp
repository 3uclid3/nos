#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/memory/block.hpp>
#include <ncxx/type-trait/conditional.hpp>
#include <ncxx/type-trait/integral-constant.hpp>
#include <ncxx/type-trait/is-trivially-copy-constructible.hpp>
#include <ncxx/type-trait/is-trivially-destructible>
#include <ncxx/type-trait/is-trivially-move-constructible.hpp>
#include <ncxx/utility/initializer-list.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

namespace NOS {

template<class T>
using ArraySizeTypeT = ConditionalT<sizeof(T) < 4 && sizeof(void*) >= 8, u64_t, u32_t>;

namespace Details {

// we inherit from our allocator to ensure we're properly aligned even for size 0 allocator class
template<typename T, typename TAllocator, typename TSize>
class ArrayBase : private TAllocator
{
public:
    using AllocatorType = TAllocator;
    using SizeType = TSize;
    using ValueType = T;

protected:
    void* _pointer{nullptr};
    SizeType _size{0};
    SizeType _capacity{0};
};

/// Helper to figure out the offset of the first element
template<typename T, typename TSize, typename TAllocator>
constexpr auto getArrayOffsetOfFirst()
{
    struct Array
    {
        using ArrayType = ArrayBase<T, TAllocator, TSize>;

        alignas(ArrayType) byte_t base[sizeof(ArrayType)];
        alignas(T) byte_t first[sizeof(T)];
    };

    return offsetof(Array, first);
}

// Base class for trivial T's
template<typename T, typename TAllocator, typename TSize>
class TrivialArrayBase : public ArrayBase<T, TAllocator, TSize>
{
};

// Base class for non-trivial T's
template<typename T, typename TAllocator, typename TSize>
class ObjectArrayBase : public ArrayBase<T, TAllocator, TSize>
{
public:
    constexpr void prepend(T&& value);
    constexpr void append(T&& value);

protected:
    static void destroyRange(T* begin, T* end);

    template<typename TItBegin, typename TItEnd>
    static void uninitializeCopy(TItBegin begin, TItEnd end);

    template<typename TItBegin, typename TItEnd>
    static void uninitializeMove(TItBegin begin, TItEnd end);

    void grow(size_t minimumSize = 0);
};

// Does T requires a TrivialArrayBase class
template<typename T>
constexpr bool IsTrivialArrayV = IsTriviallyCopyConstructibleV<T> && // not standard
                                 IsTriviallyMoveConstructibleV<T> && // but POD can't know
                                 IsTriviallyDestructibleV<T>;

template<typename T>
constexpr bool IsArrayParamByValueV = sizeof(T) <= 2 * sizeof(void*);

template<typename T>
using ArrayParamType = ConditionalT<IsArrayParamByValueV<T>, T, const T&>;

template<typename T, typename TAllocator, typename TSize>
using TypeArrayBaseT = ConditionalT<IsTrivialArrayV<T>, TrivialArrayBase<T, TAllocator, TSize>, ObjectArrayBase<T, TAllocator, TSize>>;

struct DefaultAllocator
{};

} // namespace Details

template<typename T, typename TAllocator = Details::DefaultAllocator, typename TSize = ArraySizeTypeT<T>>
class Array : public Details::TypeArrayBaseT<T, TAllocator, TSize>
{
    using Base = Details::TypeArrayBaseT<T, TAllocator, TSize>;

public:
    using typename Base::AllocatorType;

    using ValueType = T;
    using ValueParamType = Details::ArrayParamType<T>;

    using Pointer = T*;
    using ConstPointer = const T*;

    using Reference = T&;
    using ConstReference = const T&;

    class Iterator
    {
    public:
        Iterator() = default;
        Iterator(Pointer) {}
    };

    class ConstIterator
    {
    public:
        ConstIterator() = default;
        ConstIterator(ConstPointer) {}
    };

    class ReverseIterator
    {
    public:
        ReverseIterator() = default;
        ReverseIterator(Pointer) {}
    };

    class ConstReverseIterator
    {
    public:
        ConstReverseIterator() = default;
        ConstReverseIterator(ConstPointer) {}
    };

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

public:
    constexpr bool isInplaceArray() const;

protected:
    constexpr void* getAddressOfFirst() const;

private:
    constexpr void copyFrom(const Array& other);
    constexpr void moveFrom(Array&& other);
};

template<typename T, ArraySizeTypeT<T> TSize, typename TAllocator>
class EmbeddedArray : public Array<T, TAllocator>
{
    using Base = Array<T, TAllocator>;

public:
    constexpr EmbeddedArray();

private:
    alignas(T) byte_t _inplace[TSize * sizeof(T)];
};

// ---------------------------------------------------------------------------------------------

namespace Details {
template<typename T, typename TAllocator, typename TSize>
constexpr void ObjectArrayBase<T, TAllocator, TSize>::prepend(T&& value)
{
}

template<typename T, typename TAllocator, typename TSize>
constexpr void ObjectArrayBase<T, TAllocator, TSize>::append(T&& value)
{
}
} // namespace Details

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
constexpr Array<T, TAllocator, TSize>::ConstReference Array<T, TAllocator, TSize>::operator[](size_t index) const
{
    NOS_ASSERT(index < size());

    return *data()[index];
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Reference Array<T, TAllocator, TSize>::operator[](size_t index)
{
    NOS_ASSERT(index < size());

    return *data()[index];
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstReference Array<T, TAllocator, TSize>::first() const
{
    return (*this)[0];
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Reference Array<T, TAllocator, TSize>::first()
{
    return (*this)[0];
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstReference Array<T, TAllocator, TSize>::last() const
{
    NOS_ASSERT(!isEmpty());
    return (*this)[size() - 1];
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Reference Array<T, TAllocator, TSize>::last()
{
    NOS_ASSERT(!isEmpty());
    return (*this)[size() - 1];
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::ConstPointer Array<T, TAllocator, TSize>::data() const
{
    return reinterpret_cast<ConstPointer>(Base::_pointer);
}

template<typename T, typename TAllocator, typename TSize>
constexpr Array<T, TAllocator, TSize>::Pointer Array<T, TAllocator, TSize>::data()
{
    return reinterpret_cast<Pointer>(Base::_pointer);
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
    // growIfNecessary(size);
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

template<typename T, typename TAllocator, typename TSize>
constexpr bool Array<T, TAllocator, TSize>::isInplaceArray() const
{
    return Base::_pointer != getAddressOfFirst();
}

// template<typename T, typename TAllocator>
// constexpr void Array<T, TAllocator>::add(const T& value)
//{
//     const auto newSize = Base::_size + 1;
//
//     growIfNecessary(newSize);
//
//     Base::_pointer[Base::_size] = value;
//
//     Base::_size = newSize;
// }

template<typename T, typename TAllocator, typename TSize>
constexpr void* Array<T, TAllocator, TSize>::getAddressOfFirst() const
{
    /// Find the address of the first element. For this pointer math to be valid
    /// with small-size of 0 for T with lots of alignment, it's important that
    /// ArrayStorage is properly-aligned even for small-size of 0.
    return const_cast<void*>(reinterpret_cast<const void*>(reinterpret_cast<const byte_t*>(this) + Details::getArrayOffsetOfFirst<T, TSize, TAllocator>()));
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
template<typename T, ArraySizeTypeT<T> TSize, typename TAllocator>
constexpr EmbeddedArray<T, TSize, TAllocator>::EmbeddedArray()
{
    Base::_pointer = _inplace;
    Base::_capacity = TSize;
}

} // namespace NOS

#pragma clang diagnostic pop