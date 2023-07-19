#pragma once

#include <base_types.hpp>
#include <ranges/data.hpp>
#include <ranges/size.hpp>

namespace nos {

template<typename Char>
class basic_string_view
{
public:
    constexpr basic_string_view() = default;
    constexpr basic_string_view(const basic_string_view&) = default;
    constexpr basic_string_view(basic_string_view&&) = default;

    constexpr basic_string_view(nullptr_t) = delete;

    constexpr basic_string_view(const Char* str, size_t size);
    constexpr basic_string_view(const Char* cstr);

    template<typename It, typename End>
    constexpr basic_string_view(It first, End end);

    template<typename Range>
    constexpr basic_string_view(Range&& range);

    constexpr basic_string_view& operator=(const basic_string_view&) = default;
    constexpr basic_string_view& operator=(basic_string_view&&) = default;

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

using string_view = basic_string_view<char>;

template<typename Char>
constexpr basic_string_view<Char>::basic_string_view(const Char* str, size_t size)
    : _data(str)
    , _size(size)
{
}

template<typename Char>
constexpr basic_string_view<Char>::basic_string_view(const Char* cstr)
    : _data(cstr)
{
    while (*cstr++ != '\0') ++_size;
}

template<typename Char>
template<typename It, typename End>
constexpr basic_string_view<Char>::basic_string_view(It first, End end)
    : _data(first)
    , _size(end - first)
{
}

template<typename Char>
template<typename Range>
constexpr basic_string_view<Char>::basic_string_view(Range&& range)
    : _data(ranges::data(range))
    , _size(ranges::size(range))
{
}

template<typename Char>
constexpr size_t basic_string_view<Char>::size() const
{
    return _size;
}

template<typename Char>
constexpr const Char* basic_string_view<Char>::data() const
{
    return _data;
}

template<typename Char>
constexpr auto basic_string_view<Char>::begin() const
{
    return _data;
}

template<typename Char>
constexpr auto basic_string_view<Char>::end() const
{
    return _data + _size;
}

template<typename Char>
constexpr auto basic_string_view<Char>::begin()
{
    return _data;
}

template<typename Char>
constexpr auto basic_string_view<Char>::end()
{
    return _data + _size;
}

} // namespace nos
