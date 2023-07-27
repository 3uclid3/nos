#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/debug/assert.hpp>

namespace NOS {

template<typename T, size_t TAlignment = alignof(T)>
class TaggedPtr
{
public:
    static constexpr size_t MaximumBits = TAlignment - 1;

public:
    TaggedPtr() = default;
    TaggedPtr(T* ptr);
    TaggedPtr(T* ptr, size_t bits);

    T* operator=(T* ptr);
    size_t operator=(size_t bits);

    void set(T* ptr, size_t bits);

    const T* ptr() const;
    T* ptr();
    void setPtr(T* ptr);

    size_t bits() const;
    void setBits(size_t bits);

private:
    static constexpr size_t BitsMask = TAlignment - 1;
    static constexpr size_t PtrMask = ~BitsMask;

private:
    static uintptr_t asMask(T* ptr);
    static T* asPtr(uintptr_t ptr);

    static bool validatePtr(T* ptr);
    static bool validateBits(size_t bits);

private:
    T* _ptr{nullptr};
};

template<typename T, size_t TAlignment>
TaggedPtr<T, TAlignment>::TaggedPtr(T* ptr)
    : _ptr(ptr)
{
}

template<typename T, size_t TAlignment>
TaggedPtr<T, TAlignment>::TaggedPtr(T* ptr, size_t bits)
{
    set(ptr, bits);
}

template<typename T, size_t TAlignment>
T* TaggedPtr<T, TAlignment>::operator=(T* ptr)
{
    setPtr(ptr);
    return ptr;
}

template<typename T, size_t TAlignment>
size_t TaggedPtr<T, TAlignment>::operator=(size_t bits)
{
    setBits(bits);
    return bits;
}

template<typename T, size_t TAlignment>
void TaggedPtr<T, TAlignment>::set(T* ptr, size_t bits)
{
    NOS_ASSERT(validatePtr(ptr));
    NOS_ASSERT(validateBits(bits));

    _ptr = asPtr(asMask(ptr) | bits);
}

template<typename T, size_t TAlignment>
const T* TaggedPtr<T, TAlignment>::ptr() const
{
    return asPtr(asMask(_ptr) & PtrMask);
}

template<typename T, size_t TAlignment>
T* TaggedPtr<T, TAlignment>::ptr()
{
    return const_cast<T*>(const_cast<const TaggedPtr<T, TAlignment>*>(this)->ptr());
}

template<typename T, size_t TAlignment>
void TaggedPtr<T, TAlignment>::setPtr(T* ptr)
{
    NOS_ASSERT(validatePtr(ptr));

    _ptr = asPtr(asMask(ptr) | bits());
}

template<typename T, size_t TAlignment>
size_t TaggedPtr<T, TAlignment>::bits() const
{
    return asMask(_ptr) & BitsMask;
}

template<typename T, size_t TAlignment>
void TaggedPtr<T, TAlignment>::setBits(size_t bits)
{
    NOS_ASSERT(validateBits(bits));

    _ptr = asPtr(asMask(ptr()) | bits);
}

template<typename T, size_t TAlignment>
uintptr_t TaggedPtr<T, TAlignment>::asMask(T* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

template<typename T, size_t TAlignment>
T* TaggedPtr<T, TAlignment>::asPtr(uintptr_t ptr)
{
    return reinterpret_cast<T*>(ptr);
}

template<typename T, size_t TAlignment>
bool TaggedPtr<T, TAlignment>::validatePtr(T* ptr)
{
    return (asMask(ptr) & BitsMask) == 0;
}

template<typename T, size_t TAlignment>
bool TaggedPtr<T, TAlignment>::validateBits(size_t bits)
{
    return bits <= MaximumBits;
}

} // namespace NOS
