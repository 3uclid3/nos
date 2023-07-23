#include <catch2/catch_test_macros.hpp>

#include <container/span.hpp>
#include <container/static-array.hpp>
#include <string/to-string-view.hpp>

namespace NOS {

TEST_CASE("toStringView", "[String]")
{
    StaticArray<char, 64> rawBuffer;
    Span<char> buffer{rawBuffer.data(), rawBuffer.size()};

    SECTION("Binary")
    {
        SECTION("u8")
        {
            auto result = toStringView(u8_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("s8")
        {
            auto result = toStringView(s8_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("u16")
        {
            auto result = toStringView(u16_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("s16")
        {
            auto result = toStringView(s16_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("u32")
        {
            auto result = toStringView(u32_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("s32")
        {
            auto result = toStringView(s32_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("u64")
        {
            auto result = toStringView(u64_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("s64")
        {
            auto result = toStringView(s64_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }
    }

    SECTION("Decimal")
    {
        SECTION("u8")
        {
            auto result = toStringView(u8_t{42}, buffer, 10);
            CHECK(result == "42");
        }

        SECTION("s8")
        {
            auto result = toStringView(s8_t{-42}, buffer, 10);
            CHECK(result == "-42");
        }

        SECTION("u16")
        {
            auto result = toStringView(u16_t{42}, buffer, 10);
            CHECK(result == "42");
        }

        SECTION("s16")
        {
            auto result = toStringView(s16_t{-42}, buffer, 10);
            CHECK(result == "-42");
        }

        SECTION("u32")
        {
            auto result = toStringView(u32_t{42}, buffer, 10);
            CHECK(result == "42");
        }

        SECTION("s32")
        {
            auto result = toStringView(s32_t{-42}, buffer, 10);
            CHECK(result == "-42");
        }

        SECTION("u64")
        {
            auto result = toStringView(u64_t{42}, buffer, 10);
            CHECK(result == "42");
        }

        SECTION("s64")
        {
            auto result = toStringView(s64_t{-42}, buffer, 10);
            CHECK(result == "-42");
        }
    }

    SECTION("Hexadecimal")
    {
        SECTION("LowerCase")
        {
            SECTION("u8")
            {
                auto result = toStringView(u8_t{0xfe}, buffer, 16);
                CHECK(result == "fe");
            }

            SECTION("s8")
            {
                auto result = toStringView(s8_t{0x2e}, buffer, 16);
                CHECK(result == "2e");
            }

            SECTION("u16")
            {
                auto result = toStringView(u16_t{0xfefe}, buffer, 16);
                CHECK(result == "fefe");
            }

            SECTION("s16")
            {
                auto result = toStringView(s16_t{0x2e2e}, buffer, 16);
                CHECK(result == "2e2e");
            }

            SECTION("u32")
            {
                auto result = toStringView(u32_t{0xfefefefe}, buffer, 16);
                CHECK(result == "fefefefe");
            }

            SECTION("s32")
            {
                auto result = toStringView(s32_t{0x2e2e2e2e}, buffer, 16);
                CHECK(result == "2e2e2e2e");
            }

            SECTION("u64")
            {
                auto result = toStringView(u64_t{0xfefefefefefefefe}, buffer, 16);
                CHECK(result == "fefefefefefefefe");
            }

            SECTION("s64")
            {
                auto result = toStringView(s64_t{0x2e2e2e2e2e2e2e2e}, buffer, 16);
                CHECK(result == "2e2e2e2e2e2e2e2e");
            }
        }

        SECTION("UpperCase")
        {
            SECTION("u8")
            {
                auto result = toStringView(u8_t{0xFE}, buffer, 16, true);
                CHECK(result == "FE");
            }

            SECTION("s8")
            {
                auto result = toStringView(s8_t{0x2E}, buffer, 16, true);
                CHECK(result == "2E");
            }

            SECTION("u16")
            {
                auto result = toStringView(u16_t{0xFEFE}, buffer, 16, true);
                CHECK(result == "FEFE");
            }

            SECTION("s16")
            {
                auto result = toStringView(s16_t{0x2E2E}, buffer, 16, true);
                CHECK(result == "2E2E");
            }

            SECTION("u32")
            {
                auto result = toStringView(u32_t{0xFEFEFEFE}, buffer, 16, true);
                CHECK(result == "FEFEFEFE");
            }

            SECTION("s32")
            {
                auto result = toStringView(s32_t{0x2E2E2E2E}, buffer, 16, true);
                CHECK(result == "2E2E2E2E");
            }

            SECTION("u64")
            {
                auto result = toStringView(u64_t{0xFEFEFEFEFEFEFEFE}, buffer, 16, true);
                CHECK(result == "FEFEFEFEFEFEFEFE");
            }

            SECTION("s64")
            {
                auto result = toStringView(s64_t{0x2E2E2E2E2E2E2E2E}, buffer, 16, true);
                CHECK(result == "2E2E2E2E2E2E2E2E");
            }
        }
    }
}

} // namespace NOS
