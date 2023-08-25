#pragma once

#include <ncxx/hash/crc32.hpp>
#include <ncxx/string/string-view.hpp>
#include <ncxx/type-trait/decay.hpp>
#include <ncxx/type-trait/integral-constant.hpp>
#include <ncxx/type-trait/remove-pointer.hpp>
#include <ncxx/type-trait/type-full-name.hpp>
#include <ncxx/type-trait/type-name.hpp>

namespace NOS::Log {

template<typename T>
struct IsTagger : TrueType
{
};

template<typename T>
inline constexpr bool IsTaggerV = IsTagger<T>::Value;

template<typename T>
concept Tagger = IsTaggerV<T>;

struct Tag
{
    u32_t id;
    StringView name;

    constexpr bool operator==(const Tag& other) const { return id == other.id; }
};

template<typename T>
struct TagOfImpl
{
    using Type = RemovePointerT<DecayT<T>>;

    static constexpr Tag Tag{
        .id = crc32(TypeFullNameV<Type>),
        .name = TypeNameV<Type>};
};

template<typename T>
inline constexpr Tag TagOf = TagOfImpl<T>::Tag;

} // namespace NOS::Log
