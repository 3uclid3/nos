#pragma once

#include <ncxx/type-trait/is-trivially-copy-constructible.hpp>
#include <ncxx/type-trait/is-trivially-destructible>
#include <ncxx/type-trait/is-trivially-move-constructible.hpp>

namespace NOS::Details {

// Does T requires a ArrayTrivial class
template<typename T>
constexpr bool IsTrivialArrayV = IsTriviallyCopyConstructibleV<T> && // not standard
                                 IsTriviallyMoveConstructibleV<T> && // but POD can't know
                                 IsTriviallyDestructibleV<T>;

} // namespace NOS::Details
