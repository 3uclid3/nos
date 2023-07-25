#pragma once

namespace NOS {

template<typename T, T TValue>
struct IntegralConstant
{
    using ValueType = T;

    static constexpr ValueType Value = TValue;

    constexpr operator ValueType() const noexcept { return Value; }
    constexpr ValueType operator()() const noexcept { return Value; }
};

template<bool TValue>
struct BoolConstant : public IntegralConstant<bool, TValue>
{};

struct FalseType : public BoolConstant<false>
{};

struct TrueType : public BoolConstant<true>
{};

} // namespace NOS
