#pragma once

#include <ncxx/type-trait/decay.hpp>
#include <ncxx/utility/forward.hpp>
#include <ncxx/utility/move.hpp>

namespace NOS {

template<typename TFunctor>
[[nodiscard]] decltype(auto) makeScopeExit(TFunctor&& functor);

template<typename TExitFunctor>
class ScopeExit
{
public:
    template<typename TFunctor>
    explicit ScopeExit(TFunctor&& functor);
    ScopeExit(ScopeExit&& other);
    ~ScopeExit();

    ScopeExit(const ScopeExit&) = delete;

    void release();

private:
    TExitFunctor _exitFunctor;
    bool _released{false};
};

template<typename TFunctor>
inline decltype(auto) makeScopeExit(TFunctor&& functor)
{
    return ScopeExit<DecayT<TFunctor>>(forward<TFunctor>(functor));
}

template<typename TExitFunctor>
inline ScopeExit<TExitFunctor>::ScopeExit(ScopeExit&& other)
    : _exitFunctor(move(other._exitFunctor))
{
    other.release();
}

template<typename TExitFunctor>
template<typename TFunctor>
inline ScopeExit<TExitFunctor>::ScopeExit(TFunctor&& functor)
    : _exitFunctor(forward<TFunctor>(functor))
{
}

template<typename TExitFunctor>
inline ScopeExit<TExitFunctor>::~ScopeExit()
{
    if (!_released)
    {
        _exitFunctor();
    }
}

template<typename TExitFunctor>
inline void ScopeExit<TExitFunctor>::release()
{
    _released = true;
}

} // namespace NOS
