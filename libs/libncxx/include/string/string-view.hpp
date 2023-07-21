#pragma once

#include <base-types.hpp>
#include <ranges/data.hpp>
#include <ranges/size.hpp>

namespace nos {

template<typename Char>
class BasicStringView
{
public:
    constexpr BasicStringView() = default;
    constexpr BasicStringView(const BasicStringView&) = default;
    constexpr BasicStringView(BasicStringView&&) = default;

    constexpr BasicStringView(nullptr_t) = delete;

    constexpr BasicStringView(const Char* str, size_t size);
    constexpr BasicStringView(const Char* cstr);

    template<typename It, typename End>
    constexpr BasicStringView(It first, End end);

    template<typename Range>
    constexpr BasicStringView(Range&& range);

    constexpr BasicStringView& operator=(const BasicStringView&) = default;
    constexpr BasicStringView& operator=(BasicStringView&&) = default;

    constexpr size_t size() const;

    constexpr const Char* data() const;

    constexpr auto begin() const;
    constexpr auto end() const;

    constexpr auto begin();
    constexpr auto end();

private:
    const Char* _data{nullptr};
    size_t _size{0};
};

using StringView = BasicStringView<char>;

template<typename Char>
constexpr BasicStringView<Char>::BasicStringView(const Char* str, size_t size)
    : _data(str)
    , _size(size)
{
}

template<typename Char>
constexpr BasicStringView<Char>::BasicStringView(const Char* cstr)
    : _data(cstr)
{
    while (*cstr++ != '\0') ++_size;
}

template<typename Char>
template<typename It, typename End>
constexpr BasicStringView<Char>::BasicStringView(It first, End end)
    : _data(first)
    , _size(end - first)
{
}

template<typename Char>
template<typename Range>
constexpr BasicStringView<Char>::BasicStringView(Range&& range)
    : _data(ranges::data(range))
    , _size(ranges::size(range))
{
}

template<typename Char>
constexpr size_t BasicStringView<Char>::size() const
{
    return _size;
}

template<typename Char>
constexpr const Char* BasicStringView<Char>::data() const
{
    return _data;
}

template<typename Char>
constexpr auto BasicStringView<Char>::begin() const
{
    return _data;
}

template<typename Char>
constexpr auto BasicStringView<Char>::end() const
{
    return _data + _size;
}

template<typename Char>
constexpr auto BasicStringView<Char>::begin()
{
    return _data;
}

template<typename Char>
constexpr auto BasicStringView<Char>::end()
{
    return _data + _size;
}

} // namespace nos
