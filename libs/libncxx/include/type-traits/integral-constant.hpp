#pragma once

namespace nos {

template<typename T, T TValue>
struct IntegralConstant
{
    using ValueType = T;

    static constexpr ValueType Value = TValue;

    constexpr operator ValueType() const noexcept { return Value; }
    constexpr ValueType operator()() const noexcept { return Value; }
};

struct FalseType : public IntegralConstant<bool, false>
{};

struct TrueType : public IntegralConstant<bool, true>
{};

} // namespace nos
