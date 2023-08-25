#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/debug/assert.hpp>
#include <ncxx/memory/unique-ptr.hpp>
#include <ncxx/utility/forward.hpp>
#include <ncxx/utility/move.hpp>

namespace NOS {

template<typename>
class Function;

template<typename, size_t>
class InplaceFunction; // TODO

template<typename TReturn, class... TArguments>
class Function<TReturn(TArguments...)>
{
public:
    Function() = default;
    Function(const Function& other);
    Function(Function&& other);

    template<typename F>
    Function(F&& f);

    Function& operator=(const Function& other);
    Function& operator=(Function&& other);

    operator bool() const;
    TReturn operator()(TArguments... args) const;

private:
    struct Interface
    {
        virtual ~Interface() = default;
        virtual TReturn invoke(TArguments... args) const = 0;
        virtual Interface* clone() const = 0;
    };

    template<typename F>
    struct Implementation : Interface
    {
        Implementation(F&& f);

        TReturn invoke(TArguments... args) const override;
        Interface* clone() const override;

        F _f;
    };

private:
    UniquePtr<Interface> _impl;
};

template<typename TReturn, class... TArguments>
template<typename F>
Function<TReturn(TArguments...)>::Implementation<F>::Implementation(F&& func)
    : _f(forward<F>(func))
{
}

template<typename TReturn, class... TArguments>
template<typename F>
TReturn Function<TReturn(TArguments...)>::Implementation<F>::invoke(TArguments... args) const
{
    return _f(args...);
}

template<typename TReturn, class... TArguments>
template<typename F>
Function<TReturn(TArguments...)>::Interface* Function<TReturn(TArguments...)>::Implementation<F>::clone() const
{
    return new Implementation<F>(*this);
}

template<typename TReturn, class... TArguments>
Function<TReturn(TArguments...)>::Function(const Function& other)
    : _impl(other.clone())
{
}

template<typename TReturn, class... TArguments>
Function<TReturn(TArguments...)>::Function(Function&& other)
    : _impl(move(other.impl))
{
}

template<typename TReturn, class... TArguments>
template<typename F>
Function<TReturn(TArguments...)>::Function(F&& f)
    : _impl(makeUnique<Implementation<F>>(move(f)))
{
}

template<typename TReturn, class... TArguments>
Function<TReturn(TArguments...)>& Function<TReturn(TArguments...)>::operator=(const Function& other)
{
    _impl = UniquePtr<Interface>{other.clone()};
    return *this;
}

template<typename TReturn, class... TArguments>
Function<TReturn(TArguments...)>& Function<TReturn(TArguments...)>::operator=(Function&& other)
{
    _impl = move(other._impl);
    return *this;
}

template<typename TReturn, class... TArguments>
Function<TReturn(TArguments...)>::operator bool() const
{
    return _impl;
}

template<typename TReturn, class... TArguments>
TReturn Function<TReturn(TArguments...)>::operator()(TArguments... args) const
{
    NOS_ASSERT(_impl);
    return _impl->invoke(forward<TArguments>(args)...);
}

} // namespace NOS