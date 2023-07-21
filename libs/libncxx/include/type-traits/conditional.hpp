#pragma once

namespace nos {

template<bool TCondition, class TTrue, class TFalse>
struct Conditional
{
    using Type = TTrue;
};

template<class TTrue, class TFalse>
struct Conditional<false, TTrue, TFalse>
{
    using Type = TFalse;
};

template<bool TCondition, class TTrue, class TFalse>
using ConditionalT = typename Conditional<TCondition, TTrue, TFalse>::Type;

} // namespace nos
