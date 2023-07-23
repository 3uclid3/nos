#pragma once

#include <base-types.hpp>
#include <string/string-view.hpp>

namespace NOS {

class FormatArgument
{
public:
    enum class Type
    {
        Bool,
        Char,

        S8,
        S16,
        S32,
        S64,

        U8,
        U16,
        U32,
        U64,

        String
    };

    constexpr FormatArgument(bool v);
    constexpr FormatArgument(char v);

    constexpr FormatArgument(s8_t v);
    constexpr FormatArgument(s16_t v);
    constexpr FormatArgument(s32_t v);
    constexpr FormatArgument(s64_t v);

    constexpr FormatArgument(u8_t v);
    constexpr FormatArgument(u16_t v);
    constexpr FormatArgument(u32_t v);
    constexpr FormatArgument(u64_t v);

    constexpr FormatArgument(const char* cstr);
    constexpr FormatArgument(StringView sv);

    constexpr Type getType() const;

    constexpr bool asBool() const;
    constexpr char asChar() const;

    constexpr s8_t asS8() const;
    constexpr s16_t asS16() const;
    constexpr s32_t asS32() const;
    constexpr s64_t asS64() const;

    constexpr u8_t asU8() const;
    constexpr u16_t asU16() const;
    constexpr u32_t asU32() const;
    constexpr u64_t asU64() const;

    constexpr StringView asString() const;

private:
    struct RawStringView
    {
        const char* pointer;
        size_t size;
    };

    union Data
    {
        bool b;
        char c;

        s8_t s8;
        s16_t s16;
        s32_t s32;
        s64_t s64;

        u8_t u8;
        u16_t u16;
        u32_t u32;
        u64_t u64;

        RawStringView sv;
    };

    Type _type;
    Data _data;
};

constexpr FormatArgument::FormatArgument(bool v)
    : _type(Type::Bool)
{
    _data.b = v;
}

constexpr FormatArgument::FormatArgument(char v)
    : _type(Type::Char)
{
    _data.c = v;
}

constexpr FormatArgument::FormatArgument(s8_t v)
    : _type(Type::S8)
{
    _data.s8 = v;
}

constexpr FormatArgument::FormatArgument(s16_t v)
    : _type(Type::S16)
{
    _data.s16 = v;
}

constexpr FormatArgument::FormatArgument(s32_t v)
    : _type(Type::S32)
{
    _data.s32 = v;
}

constexpr FormatArgument::FormatArgument(s64_t v)
    : _type(Type::S64)
{
    _data.s64 = v;
}

constexpr FormatArgument::FormatArgument(u8_t v)
    : _type(Type::U8)
{
    _data.u8 = v;
}

constexpr FormatArgument::FormatArgument(u16_t v)
    : _type(Type::U16)
{
    _data.u16 = v;
}

constexpr FormatArgument::FormatArgument(u32_t v)
    : _type(Type::U32)
{
    _data.u32 = v;
}

constexpr FormatArgument::FormatArgument(u64_t v)
    : _type(Type::U64)
{
    _data.u64 = v;
}

constexpr FormatArgument::FormatArgument(const char* cstr)
    : FormatArgument(StringView(cstr))
{
}

constexpr FormatArgument::FormatArgument(StringView sv)
    : _type(Type::String)
{
    _data.sv = RawStringView(sv.data(), sv.size());
}

constexpr FormatArgument::Type FormatArgument::getType() const
{
    return _type;
}

constexpr bool FormatArgument::asBool() const
{
    NOS_ASSERT(_type == Type::Bool);
    return _data.b;
}

constexpr char FormatArgument::asChar() const
{
    NOS_ASSERT(_type == Type::Char);
    return _data.c;
}

constexpr s8_t FormatArgument::asS8() const
{
    NOS_ASSERT(_type == Type::S8);
    return _data.s8;
}

constexpr s16_t FormatArgument::asS16() const
{
    NOS_ASSERT(_type == Type::S16);
    return _data.s16;
}

constexpr s32_t FormatArgument::asS32() const
{
    NOS_ASSERT(_type == Type::S32);
    return _data.s32;
}

constexpr s64_t FormatArgument::asS64() const
{
    NOS_ASSERT(_type == Type::S64);
    return _data.s64;
}

constexpr u8_t FormatArgument::asU8() const
{
    NOS_ASSERT(_type == Type::U8);
    return _data.u8;
}

constexpr u16_t FormatArgument::asU16() const
{
    NOS_ASSERT(_type == Type::U16);
    return _data.u16;
}

constexpr u32_t FormatArgument::asU32() const
{
    NOS_ASSERT(_type == Type::U32);
    return _data.u32;
}

constexpr u64_t FormatArgument::asU64() const
{
    NOS_ASSERT(_type == Type::U64);
    return _data.u64;
}

constexpr StringView FormatArgument::asString() const
{
    NOS_ASSERT(_type == Type::String);
    return {_data.sv.pointer, _data.sv.size};
}

} // namespace NOS
