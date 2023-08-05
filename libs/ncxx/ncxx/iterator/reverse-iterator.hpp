#pragma once

namespace NOS {

template<typename TIterator>
class ReverseIterator
{
public:
    using IteratorType = TIterator;

public:
    constexpr ReverseIterator() = default;
    constexpr ReverseIterator(IteratorType pointer);

    constexpr bool operator==(const ReverseIterator& other) const = default;

    constexpr auto operator*() const;
    constexpr auto operator->() const;

    constexpr ReverseIterator& operator++();
    constexpr ReverseIterator operator++(int);

private:
    IteratorType _iterator{};
};

} // namespace NOS
