#include <catch2/catch_test_macros.hpp>

#include <ncxx/container/static-array.hpp>
#include <ncxx/string/format-to.hpp>
#include <ncxx/string/string-view.hpp>

namespace NOS {

struct Out
{
    void write(char c)
    {
        REQUIRE(_bufferSize < _buffer.size());

        _buffer[_bufferSize++] = c;
    }

    StringView view() const
    {
        return {_buffer.data(), _bufferSize};
    }

    // TODO use an Array
    StaticArray<char, 256> _buffer;
    size_t _bufferSize{0};
};

TEST_CASE("formatTo - bool", "[String]")
{
    Out out;

    formatTo(out, "Format a bool '{}'", true);

    StringView sv = out.view();

    CHECK(sv == "Format a bool 'true'");
}

TEST_CASE("formatTo - char", "[String]")
{
    Out out;

    formatTo(out, "Format a char '{}'", 'c');

    StringView sv = out.view();

    CHECK(sv == "Format a char 'c'");
}

TEST_CASE("formatTo - s8_t", "[String]")
{
    Out out;

    formatTo(out, "Format a s8 '{}'", s8_t{-42});

    StringView sv = out.view();

    CHECK(sv == "Format a s8 '-42'");
}

TEST_CASE("formatTo - u8_t", "[String]")
{
    Out out;

    formatTo(out, "Format a u8 '{}'", u8_t{42});

    StringView sv = out.view();

    CHECK(sv == "Format a u8 '42'");
}

TEST_CASE("formatTo - s16_t", "[String]")
{
    Out out;

    formatTo(out, "Format a s16 '{}'", s16_t{-42});

    StringView sv = out.view();

    CHECK(sv == "Format a s16 '-42'");
}

TEST_CASE("formatTo - u16_t", "[String]")
{
    Out out;

    formatTo(out, "Format a u16 '{}'", u16_t{42});

    StringView sv = out.view();

    CHECK(sv == "Format a u16 '42'");
}

TEST_CASE("formatTo - s32_t", "[String]")
{
    Out out;

    formatTo(out, "Format a s32_t '{}'", s32_t{-42});

    StringView sv = out.view();

    CHECK(sv == "Format a s32_t '-42'");
}

TEST_CASE("formatTo - u32_t", "[String]")
{
    Out out;

    formatTo(out, "Format a u32 '{}'", u32_t{42});

    StringView sv = out.view();

    CHECK(sv == "Format a u32 '42'");
}

TEST_CASE("formatTo - s64_t", "[String]")
{
    Out out;

    formatTo(out, "Format a s64 '{}'", s64_t{-42});

    StringView sv = out.view();

    CHECK(sv == "Format a s64 '-42'");
}

TEST_CASE("formatTo - u64_t", "[String]")
{
    Out out;

    formatTo(out, "Format a u64 '{}'", u64_t{42});

    StringView sv = out.view();

    CHECK(sv == "Format a u64 '42'");
}

TEST_CASE("formatTo - String", "[String]")
{
    Out out;

    formatTo(out, "Format a string '{}'", "A String");

    StringView sv = out.view();

    CHECK(sv == "Format a string 'A String'");
}

TEST_CASE("formatTo - binary presentation", "[String]")
{
    Out out;

    SECTION("LowerCase")
    {
        formatTo(out, "Format to binary '{:b}'", 0b101010);

        StringView sv = out.view();

        CHECK(sv == "Format to binary '101010'");
    }

    SECTION("UpperCase")
    {
        formatTo(out, "Format to binary '{:B}'", 0B101010);

        StringView sv = out.view();

        CHECK(sv == "Format to binary '101010'");
    }
}

TEST_CASE("formatTo - hex presentation", "[String]")
{
    Out out;

    SECTION("LowerCase")
    {
        formatTo(out, "Format to hex '{:x}'", 0xfefefefe);

        StringView sv = out.view();

        CHECK(sv == "Format to hex 'fefefefe'");
    }

    SECTION("UpperCase")
    {
        formatTo(out, "Format to hex '{:X}'", 0xFEFEFEFE);

        StringView sv = out.view();

        CHECK(sv == "Format to hex 'FEFEFEFE'");
    }
}

TEST_CASE("formatTo - position", "[String]")
{
    Out out;

    formatTo(out, "Format at 1: {1}; at 2 {2}; at 0 {0}", 42, 22, 24);

    StringView sv = out.view();

    CHECK(sv == "Format at 1: 22; at 2 24; at 0 42");
}

} // namespace NOS
