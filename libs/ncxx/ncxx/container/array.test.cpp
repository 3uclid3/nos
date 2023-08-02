#include <ncxx/container/array.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/memory/allocator/stack-allocator.hpp>
#include <ncxx/test/asan.hpp>

namespace NOS {

TEST_CASE("Capacity", "[Array]")
{
    using TestArray = Array<int>;
    SECTION("default ctor")
    {
        TestArray a;
        CHECK(a.capacity() == 0);
        CHECK(Test::isContiguousContainerASanCorrect(a));
    }

    SECTION("ctor with initial size")
    {
        TestArray a(100);
        CHECK(a.capacity() == 100);

        a.append(TestArray::ValueType{});

        CHECK(a.capacity() > 101);
        CHECK(Test::isContiguousContainerASanCorrect(a));
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

    TestArray a;

    a.reserve(10);

    CHECK(a.capacity() >= 10);
    CHECK(Test::isContiguousContainerASanCorrect(a));
}

} // namespace NOS
