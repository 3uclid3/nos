#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/memory/new.hpp>
#include <ncxx/type-trait/add-lvalue-reference.hpp>
#include <ncxx/type-trait/is-base-of.hpp>
#include <ncxx/type-trait/is-same.hpp>
#include <ncxx/utility/forward.hpp>

namespace NOS {

template<typename T>
struct DefaultDeleter
{
    void operator()(T* pointer)
    {
        delete pointer;
    }
};

template<typename T, typename TDeleter = DefaultDeleter<T>>
class UniquePtr : private TDeleter
{
public:
    using Pointer = T*;

public:
    constexpr UniquePtr() = default;
    constexpr UniquePtr(nullptr_t);

    explicit UniquePtr(T* pointer);

    template<typename U, typename TUDeleter>
    UniquePtr(UniquePtr<U, TUDeleter>&& other);

    UniquePtr(UniquePtr&& other);
    UniquePtr& operator=(UniquePtr&& other);

    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    ~UniquePtr();

public:
    [[nodiscard]] T* get() const;
    [[nodiscard]] T* release();

    [[nodiscard]] operator bool() const;

    [[nodiscard]] AddLValueReferenceT<T> operator*() const;
    [[nodiscard]] T* operator->() const;

private:
    T* _pointer{nullptr};
};
template<class T, class... TArguments>
inline constexpr UniquePtr<T> makeUnique(TArguments&&... args)
{
    return UniquePtr<T>(new T(forward<TArguments>(args)...));
}

template<typename T, typename TDeleter>
class UniquePtr<T[], TDeleter>
{
};

template<typename T, typename TDeleter>
constexpr UniquePtr<T, TDeleter>::UniquePtr(nullptr_t)
{}

template<typename T, typename TDeleter>
UniquePtr<T, TDeleter>::UniquePtr(T* pointer)
    : _pointer(pointer)
{
}
template<typename T, typename TDeleter>
template<typename U, typename TUDeleter>
UniquePtr<T, TDeleter>::UniquePtr(UniquePtr<U, TUDeleter>&& other)
    : _pointer(other.release())
{
}

template<typename T, typename TDeleter>
UniquePtr<T, TDeleter>::UniquePtr(UniquePtr&& other)
    : _pointer(other.release())
{
}

template<typename T, typename TDeleter>
UniquePtr<T, TDeleter>& UniquePtr<T, TDeleter>::operator=(UniquePtr&& other)
{
    _pointer = other._pointer;
    other._pointer = nullptr;
    return *this;
}

template<typename T, typename TDeleter>
UniquePtr<T, TDeleter>::~UniquePtr()
{
    TDeleter::operator()(_pointer);
}

template<typename T, typename TDeleter>
T* UniquePtr<T, TDeleter>::get() const
{
    return _pointer;
}

template<typename T, typename TDeleter>
T* UniquePtr<T, TDeleter>::release()
{
    T* pointer = _pointer;
    _pointer = nullptr;
    return pointer;
}

template<typename T, typename TDeleter>
UniquePtr<T, TDeleter>::operator bool() const
{
    return _pointer != nullptr;
}

template<typename T, typename TDeleter>
AddLValueReferenceT<T> UniquePtr<T, TDeleter>::operator*() const
{
    return *_pointer;
}

template<typename T, typename TDeleter>
T* UniquePtr<T, TDeleter>::operator->() const
{
    return _pointer;
}

} // namespace NOS