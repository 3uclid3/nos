#include <ncxx/container/array.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/memory/allocator/stack-allocator.hpp>
#include <ncxx/test/object.fake.hpp>

namespace NOS {

static constexpr size_t StackBufferSize = 8192;
using TestArray = Array<int, Memory::StackAllocator<StackBufferSize, alignOf<int>()>>;

TEST_CASE("Capacity", "[Array]")
{
    SECTION("default ctor")
    {
        TestArray a;
        CHECK(a.capacity() == 0);
    }

    SECTION("ctor with initial size")
    {
        TestArray a(100);
        CHECK(a.capacity() == 100);

        a.append(TestArray::ValueType{});

        CHECK(a.capacity() > 101);
    }
}

TEST_CASE("isEmpty", "[Array]")
{
    TestArray a;
    CHECK(a.isEmpty());

    a.append(TestArray::ValueType{});
    CHECK_FALSE(a.isEmpty());

    a.clear();
    CHECK(a.isEmpty());
}

TEST_CASE("reserve", "[Array]")
{
    SECTION("allocate at least size")
    {
        TestArray a;
        a.reserve(10);

        CHECK(a.isEmpty());
        CHECK(a.capacity() >= 10);
    }

    SECTION("does nothing if capacity is equal or higher than requested size")
    {
        TestArray a;
        a.reserve(100);
        CHECK(a.isEmpty());
        CHECK(a.capacity() == 100);

        a.reserve(50);
        CHECK(a.isEmpty());
        CHECK(a.capacity() == 100);

        a.reserve(100);
        CHECK(a.isEmpty());
        CHECK(a.capacity() == 100);
    }

    SECTION("allocate a new buffer capacity is lower than requested size")
    {
        TestArray a;
        a.reserve(100);
        CHECK(a.isEmpty());
        CHECK(a.capacity() == 100);

        a.reserve(150);
        CHECK(a.isEmpty());
        CHECK(a.capacity() >= 150);
    }

    SECTION("content is moved to new buffer")
    {
        TestArray a(100);
        CHECK(a.size() == 100);
        CHECK(a.capacity() == 100);

        a.reserve(150);
        CHECK(a.size() == 100);
        CHECK(a.capacity() >= 150);
    }
}

TEST_CASE("resize(size)", "[Array]")
{
    SECTION("copyable/moveable")
    {
        TestArray a(100);
        a.resize(50);
        CHECK(a.size() == 50);
        CHECK(a.capacity() == 100);

        a.resize(200);
        CHECK(a.size() == 200);
        CHECK(a.capacity() >= 200);
    }
    SECTION("moveable only")
    {
        using TestMoveOnlyArray = Array<Fake::MoveOnlyObject, Memory::StackAllocator<StackBufferSize, alignOf<Fake::MoveOnlyObject>()>>;

        TestMoveOnlyArray a(100);
        a.resize(50);
        CHECK(a.size() == 50);
        CHECK(a.capacity() == 100);

        a.resize(200);
        CHECK(a.size() == 200);
        CHECK(a.capacity() >= 200);
    }
}

TEST_CASE("resize(size, value)", "[Array]")
{
    TestArray a(100);

    a.resize(50, 1);
    CHECK(a.size() == 50);
    CHECK(a.capacity() == 100);
    //  CHECK(a == TestArray(50));

    a.resize(200, 1);
    CHECK(a.size() == 200);
    CHECK(a.capacity() >= 200);

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

    using TestFailArray = Array<Fail, Memory::StackAllocator<StackBufferSize, alignOf<Fail>()>>;

    SECTION("non-const")
    {
        SECTION("Empty")
        {
            TestArray a;
            CHECK(a.data() == nullptr);
        }

        SECTION("Non-Empty")
        {
            TestArray a(100);
            CHECK(a.data() == addressOf(a.first()));
        }

        SECTION("Dereference")
        {
            TestFailArray a(100);
            CHECK(a.data() == addressOf(a.first()));
        }
    }

    SECTION("const")
    {
        SECTION("Empty")
        {
            const TestArray a{};
            CHECK(a.data() == nullptr);
        }

        SECTION("Non-Empty")
        {
            const TestArray a(100);
            CHECK(a.data() == addressOf(a.first()));
        }

        SECTION("Dereference")
        {
            const TestFailArray a(100);
            CHECK(a.data() == addressOf(a.first()));
        }
    }
}

} // namespace NOS
