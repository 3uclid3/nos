#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/container/static-array.hpp>
#include <ncxx/string/string-view.hpp>
#include <ncxx/type-list/types-size.hpp>
#include <ncxx/type-trait/is-enum.hpp>
#include <ncxx/type-trait/type-enum-value-name.hpp>
#include <ncxx/type-trait/underlying-type.hpp>
#include <ncxx/utility/integer-sequence.hpp>

namespace NOS {

template<typename TEnum, TEnum TSize>
class EnumString
{
public:
    using EnumType = TEnum;

    static constexpr size_t Size = static_cast<size_t>(TSize);

public:
    using ConstIterator = typename StaticArray<StringView, Size>::ConstIterator;

public:
    EnumString(const EnumString& other) = delete;
    EnumString(EnumString&& other) = delete;

    EnumString& operator=(const EnumString& other) = delete;
    EnumString& operator=(EnumString&& other) = delete;

public:
    constexpr EnumString();

    constexpr StringView string(TEnum value) const;
    constexpr TEnum value(StringView string, TEnum invalid = TEnum{-1}) const;

    constexpr StringView operator[](size_t index) const;
    constexpr size_t size() const;

    constexpr ConstIterator begin() const;
    constexpr ConstIterator end() const;

    constexpr ConstIterator cbegin() const;
    constexpr ConstIterator cend() const;

private:
    template<size_t... TIndex>
    constexpr void initializeSequence(IndexSequence<TIndex...>);

private:
    StaticArray<StringView, Size> _strings{};
};

template<typename TEnum, TEnum TSize>
constexpr EnumString<TEnum, TSize>::EnumString()
{
    initializeSequence(MakeIntegerSequence<size_t, Size>());
}

template<typename TEnum, TEnum TSize>
constexpr StringView EnumString<TEnum, TSize>::string(TEnum value) const
{
    return _strings[static_cast<size_t>(value)];
}

template<typename TEnum, TEnum TSize>
constexpr TEnum EnumString<TEnum, TSize>::value(StringView string, TEnum invalid) const
{
    for (size_t i = 0; i < size(); ++i)
    {
        if (_strings[i] == string)
        {
            return static_cast<TEnum>(i);
        }
    }

    return invalid;
}

template<typename TEnum, TEnum TSize>
constexpr StringView EnumString<TEnum, TSize>::operator[](size_t index) const
{
    return _strings[index];
}

template<typename TEnum, TEnum TSize>
constexpr size_t EnumString<TEnum, TSize>::size() const
{
    return Size;
}

template<typename TEnum, TEnum TSize>
constexpr typename EnumString<TEnum, TSize>::ConstIterator EnumString<TEnum, TSize>::begin() const
{
    return _strings.begin();
}

template<typename TEnum, TEnum TSize>
constexpr typename EnumString<TEnum, TSize>::ConstIterator EnumString<TEnum, TSize>::end() const
{
    return _strings.end();
}

template<typename TEnum, TEnum TSize>
constexpr typename EnumString<TEnum, TSize>::ConstIterator EnumString<TEnum, TSize>::cbegin() const
{
    return _strings.cbegin();
}

template<typename TEnum, TEnum TSize>
constexpr typename EnumString<TEnum, TSize>::ConstIterator EnumString<TEnum, TSize>::cend() const
{
    return _strings.cend();
}

template<typename TEnum, TEnum TSize>
template<size_t... TIndex>
constexpr void EnumString<TEnum, TSize>::initializeSequence(IndexSequence<TIndex...>)
{
    ((_strings[TIndex] = TypeEnumValueNameV<TEnum, TEnum{TIndex}>), ...);
}

} // namespace NOS
