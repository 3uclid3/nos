#include <ncxx/container/details/array-trivial.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/memory/allocator/stack-allocator.hpp>

namespace NOS::Details {

using TestArray = ArrayTrivial<int, Memory::StackAllocator<8096, alignOf<int>()>, size_t>;

TEST_CASE("prepend", "[Array], [ArrayTrivial]")
{
    TestArray array;

    for (int i = 0; i < 150; ++i)
    {
        array.prepend(i);

        REQUIRE(array.size() == static_cast<size_t>(i + 1));

        for (int j = 0; j <= i; ++j)
        {
            CHECK(array[static_cast<size_t>(j)] == i - j);
        }
    }
}

TEST_CASE("append", "[Array], [ArrayTrivial]")
{
    TestArray array;

    for (int i = 0; i < 150; ++i)
    {
        array.append(i);

        REQUIRE(array.size() == static_cast<size_t>(i + 1));

        for (int j = 0; j <= i; ++j)
        {
            CHECK(array[static_cast<size_t>(j)] == j);
        }
    }
}

TEST_CASE("removeAt", "[Array], [ArrayTrivial]")
{
    TestArray array{10};
    REQUIRE(array.size() == 10);
    for (size_t i = 0; i < array.size(); ++i) array[i] = static_cast<int>(i);

    array.removeAt(5);
    CHECK(array.size() == 9);
    CHECK(array[5] == 6);

    array.removeAt(2);
    CHECK(array.size() == 8);
    CHECK(array[2] == 3);

    array.removeAt(2);
    CHECK(array.size() == 7);
    CHECK(array[2] == 4);
}

TEST_CASE("removeAtSwapLast", "[Array], [ArrayTrivial]")
{
    TestArray array{10};
    REQUIRE(array.size() == 10);
    for (size_t i = 0; i < array.size(); ++i) array[i] = static_cast<int>(i);

    array.removeAtSwapLast(5);
    CHECK(array.size() == 9);
    CHECK(array[5] == 9);

    array.removeAtSwapLast(2);
    CHECK(array.size() == 8);
    CHECK(array[2] == 8);

    array.removeAtSwapLast(2);
    CHECK(array.size() == 7);
    CHECK(array[2] == 7);
}

TEST_CASE("removeOne", "[Array], [ArrayTrivial]")
{
    TestArray array{10};
    REQUIRE(array.size() == 10);
    for (size_t i = 0; i < array.size(); ++i) array[i] = static_cast<int>(i);

    array.removeOne(5);
    CHECK(array.size() == 9);
    CHECK(array[5] == 6);

    array.removeOne(2);
    CHECK(array.size() == 8);
    CHECK(array[2] == 3);

    array.removeOne(2);
    CHECK(array.size() == 8);
    CHECK(array[2] == 3);
}

TEST_CASE("removeOneSwapLast", "[Array], [ArrayTrivial]")
{
    TestArray array{10};
    REQUIRE(array.size() == 10);
    for (size_t i = 0; i < array.size(); ++i) array[i] = static_cast<int>(i);

    array.removeOneSwapLast(5);
    CHECK(array.size() == 9);
    CHECK(array[5] == 9);

    array.removeOneSwapLast(2);
    CHECK(array.size() == 8);
    CHECK(array[2] == 8);

    array.removeOneSwapLast(3);
    CHECK(array.size() == 7);
    CHECK(array[3] == 7);

    array.removeOneSwapLast(3);
    CHECK(array.size() == 7);
}

TEST_CASE("removeFirst", "[Array], [ArrayTrivial]")
{
    TestArray array{10};
    REQUIRE(array.size() == 10);
    for (size_t i = 0; i < array.size(); ++i) array[i] = static_cast<int>(i);

    array.removeFirst();
    CHECK(array.size() == 9);
    CHECK(array[0] == 1);

    array.removeFirst();
    CHECK(array.size() == 8);
    CHECK(array[0] == 2);

    array.removeFirst();
    CHECK(array.size() == 7);
    CHECK(array[0] == 3);
}

TEST_CASE("removeFirstSwapLast", "[Array], [ArrayTrivial]")
{
    TestArray array{10};
    REQUIRE(array.size() == 10);
    for (size_t i = 0; i < array.size(); ++i) array[i] = static_cast<int>(i);

    array.removeFirstSwapLast();
    CHECK(array.size() == 9);
    CHECK(array.first() == 9);

    array.removeFirstSwapLast();
    CHECK(array.size() == 8);
    CHECK(array.first() == 8);

    array.removeFirstSwapLast();
    CHECK(array.size() == 7);
    CHECK(array.first() == 7);
}

TEST_CASE("removeLast", "[Array], [ArrayTrivial]")
{
    TestArray array{10};
    REQUIRE(array.size() == 10);

    array.removeLast();
    CHECK(array.size() == 9);

    array.removeLast();
    CHECK(array.size() == 8);

    array.removeLast();
    CHECK(array.size() == 7);
}

TEST_CASE("resize", "[Array], [ArrayTrivial]")
{
    TestArray array;
    array.resize(32);

    CHECK(array.size() == 32);
    for (size_t i = 0; i < array.size(); ++i) array[i] = static_cast<int>(i);

    array.resize(64);
    for (size_t i = 0; i < 32; ++i)
    {
        CHECK(array[i] == static_cast<int>(i));
    }
}

TEST_CASE("resize value", "[Array], [ArrayTrivial]")
{
    TestArray array;
    array.resize(32, 8);
    for (size_t i = 0; i < 32; ++i)
    {
        CHECK(array[i] == 8);
    }

    CHECK(array.size() == 32);
    for (size_t i = 0; i < array.size(); ++i) array[i] = static_cast<int>(i);

    array.resize(64, 12);
    for (size_t i = 0; i < 32; ++i)
    {
        CHECK(array[i] == static_cast<int>(i));
    }
    for (size_t i = 32; i < 64; ++i)
    {
        CHECK(array[i] == 12);
    }
}

} // namespace NOS::Details