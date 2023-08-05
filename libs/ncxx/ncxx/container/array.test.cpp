#include <ncxx/container/array.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/memory/address-of.hpp>
#include <ncxx/memory/allocator/stack-allocator.hpp>
#include <ncxx/test/asan.hpp>

namespace NOS {

struct MoveOnly
{
    MoveOnly() = default;

    MoveOnly(MoveOnly&&) = default;
    MoveOnly& operator=(MoveOnly&&) = default;

    MoveOnly(const MoveOnly&) = delete;
    const MoveOnly& operator=(const MoveOnly&) = delete;

    int value{};
};

TEST_CASE("Capacity", "[Array]")
{
    using TestArray = Array<int>;
    SECTION("default ctor")
    {
        TestArray a;
        CHECK(a.capacity() == 0);
        CHECK(ASan::verifyContiguousContainer(a));
    }

    SECTION("ctor with initial size")
    {
        TestArray a(100);
        CHECK(a.capacity() == 100);

        a.append(TestArray::ValueType{});

        CHECK(a.capacity() > 101);
        CHECK(ASan::verifyContiguousContainer(a));
    }
}

TEST_CASE("isEmpty", "[Array]")
{
    using TestArray = Array<int>;

    TestArray a;
    CHECK(a.isEmpty());

    a.append(TestArray::ValueType{});
    CHECK_FALSE(a.isEmpty());

    a.clear();
    CHECK(a.isEmpty());
}

TEST_CASE("reserve", "[Array]")
{
    using TestArray = Array<int>;

    SECTION("allocate at least size")
    {
        TestArray a;
        a.reserve(10);

        CHECK(a.isEmpty());
        CHECK(a.capacity() >= 10);
        CHECK(ASan::verifyContiguousContainer(a));
    }

    SECTION("does nothing if capacity is equal or higher than requested size")
    {
        TestArray a;
        a.reserve(100);
        CHECK(a.isEmpty());
        CHECK(a.capacity() == 100);

        a.reserve(50);
        CHECK(a.isEmpty());
        CHECK(a.capacity() == 50);

        a.reserve(100);
        CHECK(a.isEmpty());
        CHECK(a.capacity() == 100);

        CHECK(ASan::verifyContiguousContainer(a));
    }

    SECTION("allocate a new buffer capacity is lower than requested size")
    {
        TestArray a;
        a.reserve(100);
        CHECK(a.isEmpty());
        CHECK(a.capacity() == 100);

        a.reserve(150);
        CHECK(a.isEmpty());
        CHECK(a.capacity() == 150);

        CHECK(ASan::verifyContiguousContainer(a));
    }

    SECTION("content is moved to new buffer")
    {
        TestArray a(100);
        CHECK(a.size() == 100);
        CHECK(a.capacity() == 100);

        a.reserve(150);
        CHECK(a.size() == 100);
        CHECK(a.capacity() == 150);

        CHECK(ASan::verifyContiguousContainer(a));
    }
}

TEST_CASE("resize(size)", "[Array]")
{
    SECTION("copyable/moveable")
    {
        using TestArray = Array<int>;

        TestArray a(100);
        a.resize(50);
        CHECK(a.size() == 50);
        CHECK(a.capacity() == 100);
        CHECK(ASan::verifyContiguousContainer(a));

        a.resize(200);
        CHECK(a.size() == 200);
        CHECK(a.capacity() >= 200);
        CHECK(ASan::verifyContiguousContainer(a));
    }
    SECTION("moveable only")
    {
        using TestArray = Array<MoveOnly>;

        TestArray a(100);
        a.resize(50);
        CHECK(a.size() == 50);
        CHECK(a.capacity() == 100);
        CHECK(ASan::verifyContiguousContainer(a));

        a.resize(200);
        CHECK(a.size() == 200);
        CHECK(a.capacity() >= 200);
        CHECK(ASan::verifyContiguousContainer(a));
    }
}

TEST_CASE("resize(size, value)", "[Array]")
{
    using TestArray = Array<int>;

    TestArray a(100);

    a.resize(50, 1);
    CHECK(a.size() == 50);
    CHECK(a.capacity() == 100);
    CHECK(a == Array<int>(50));

    a.resize(200, 1);
    CHECK(a.size() == 200);
    CHECK(a.capacity() >= 200);
    CHECK(ASan::verifyContiguousContainer(a));

    for (unsigned i = 0; i < 50; ++i)
    {
        CHECK(a[i] == 0);
    }

    for (unsigned i = 50; i < 200; ++i)
    {
        CHECK(a[i] == 1);
    }
}

TEST_CASE("size", "[Array]")
{
    using TestArray = Array<int>;

    TestArray a;

    CHECK(a.size() == 0);
    a.append(0);

    CHECK(a.size() == 1);
    a.append(1);

    CHECK(a.size() == 2);
    a.append(2);

    CHECK(a.size() == 3);

    a.removeLast();
    CHECK(a.size() == 2);

    a.removeLast();
    CHECK(a.size() == 1);

    a.removeLast();
    CHECK(a.size() == 0);
}

TEST_CASE("data", "[Array]")
{
    struct Fail
    {
        // clang-format off
        constexpr Fail() = default;
        constexpr Fail(int i) : v(i) {}
        constexpr ~Fail() {}
        Fail* operator&() const { FAIL(); return nullptr; }
        int v{};
        // clang-format on
    };

    SECTION("non-const")
    {
        SECTION("Empty")
        {
            using TestArray = Array<int>;

            TestArray a;
            CHECK(a.data() == nullptr);
        }

        SECTION("Non-Empty")
        {
            using TestArray = Array<int>;

            TestArray a(100);
            CHECK(a.data() == addressOf(a.first()));
        }

        SECTION("Dereference")
        {
            using TestArray = Array<Fail>;

            TestArray a(100);
            CHECK(a.data() == addressOf(a.first()));
        }
    }

    SECTION("const")
    {
        SECTION("Empty")
        {
            using TestArray = Array<int>;

            const TestArray a;
            CHECK(a.data() == nullptr);
        }

        SECTION("Non-Empty")
        {
            using TestArray = Array<int>;

            const TestArray a(100);
            CHECK(a.data() == addressOf(a.first()));
        }

        SECTION("Dereference")
        {
            using TestArray = Array<Fail>;

            const TestArray a(100);
            CHECK(a.data() == addressOf(a.first()));
        }
    }
}

} // namespace NOS
