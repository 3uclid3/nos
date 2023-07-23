#pragma once

#include <container/span.hpp>
#include <string/string-view.hpp>

// TODO Extract formatting code to libncxx

namespace NOS::Log {

class FormatArgument
{
public:
    enum class Type
    {
        Bool,
        Char,

        SInt8,
        SInt16,
        SInt32,
        SInt64,

        UInt8,
        UInt16,
        UInt32,
        UInt64,

        String
    };

public:
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

    constexpr FormatArgument(const char* v);
    constexpr FormatArgument(StringView v);

    constexpr Type getType() const;

    constexpr StringView asString() const;

private:
    struct SimpleStringView
    {
        const char* ptr;
        size_t size;
    };

    Type _type;
    union
    {
        bool b;
        char ch;

        s8_t s8;
        s16_t s16;
        s32_t s32;
        s64_t s64;

        u8_t u8;
        u16_t u16;
        u32_t u32;
        u64_t u64;

        SimpleStringView sv;
    } _data;
};

void printc(char c);
void print(StringView msg);
void vprintf(StringView fmt, Span<FormatArgument> arguments);

template<typename... TArgs>
void printf(StringView fmt, const TArgs&... args);

template<typename... TArgs>
void info(StringView fmt, const TArgs&... args);

template<typename... TArgs>
void warn(StringView fmt, const TArgs&... args);

template<typename... TArgs>
void error(StringView fmt, const TArgs&... args);

constexpr FormatArgument::FormatArgument(bool v)
    : _type(Type::Bool)
{
    _data.b = v;
}

constexpr FormatArgument::FormatArgument(char v)
    : _type(Type::Char)
{
    _data.ch = v;
}

constexpr FormatArgument::FormatArgument(s8_t v)
    : _type(Type::SInt8)
{
    _data.s8 = v;
}

constexpr FormatArgument::FormatArgument(s16_t v)
    : _type(Type::SInt16)
{
    _data.s16 = v;
}

constexpr FormatArgument::FormatArgument(s32_t v)
    : _type(Type::SInt32)
{
    _data.s32 = v;
}

constexpr FormatArgument::FormatArgument(s64_t v)
    : _type(Type::SInt64)
{
    _data.s64 = v;
}

constexpr FormatArgument::FormatArgument(u8_t v)
    : _type(Type::UInt8)
{
    _data.u8 = v;
}

constexpr FormatArgument::FormatArgument(u16_t v)
    : _type(Type::UInt16)
{
    _data.u16 = v;
}

constexpr FormatArgument::FormatArgument(u32_t v)
    : _type(Type::UInt32)
{
    _data.u32 = v;
}

constexpr FormatArgument::FormatArgument(u64_t v)
    : _type(Type::UInt64)
{
    _data.u64 = v;
}

constexpr FormatArgument::FormatArgument(const char* v)
    : _type(Type::String)
{
    StringView sv{v};
    _data.sv = {sv.data(), sv.size()};
}

constexpr FormatArgument::FormatArgument(StringView v)
    : _type(Type::String)
{
    _data.sv = {v.data(), v.size()};
}

constexpr FormatArgument::Type FormatArgument::getType() const
{
    return _type;
}

constexpr StringView FormatArgument::asString() const
{
    return StringView{_data.sv.ptr, _data.sv.size};
}

template<typename... TArgs>
void printf(StringView fmt, const TArgs&... args)
{
    if constexpr (sizeof...(TArgs) > 0)
    {
        FormatArgument fmtArgs[] = {args...};
        vprintf(fmt, Span<FormatArgument>(fmtArgs));
    }
    else
    {
        print(fmt);
    }
}

template<typename... TArgs>
void info(StringView fmt, const TArgs&... args)
{
    print("[\033[36mINFO\033[0m] ");
    printf(fmt, args...);
    printc('\n');
}

template<typename... TArgs>
void warn(StringView fmt, const TArgs&... args)
{
    print("[\033[33mWARN\033[0m] ");
    printf(fmt, args...);
    printc('\n');
}

template<typename... TArgs>
void error(StringView fmt, const TArgs&... args)
{
    print("[\033[31mERROR\033[0m] ");
    printf(fmt, args...);
    printc('\n');
}

} // namespace NOS::Log
