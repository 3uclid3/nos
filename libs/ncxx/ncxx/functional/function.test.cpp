#include <ncxx/functional/function.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/basic-types.hpp>

namespace NOS {

namespace {

static bool freeCalled{false};

void free()
{
    freeCalled = true;
}

struct Class
{
    void member()
    {
        called = true;
    }

    void cmember() const
    {
        called = true;
    }

    void memberWithArgument(int argument)
    {
        called = true;
        calledArgument = argument;
    }

    void cmemberWithArgument(int argument) const
    {
        called = true;
        calledArgument = argument;
    }

    static void staticMember()
    {
        staticCalled = true;
    }

    static void staticMemberWithArgument(int argument)
    {
        staticCalled = true;
        staticCalledArgument = argument;
    }

    mutable bool called{false};
    mutable int calledArgument{0};

    inline static bool staticCalled{false};
    inline static int staticCalledArgument{0};
};

} // namespace

TEST_CASE("Empty", "[Function]")
{
    Function<void()> function;

    CHECK_FALSE(function);
}

TEST_CASE("Free", "[Function]")
{
    Function<void()> function{&free};

    function();

    CHECK(freeCalled);
}

TEST_CASE("Lambda", "[Function]")
{
    Function<void()> function;

    SECTION("without capture")
    {
        static bool called;

        function = []() { called = true; };
        function();

        CHECK(called);
    }

    SECTION("with capture")
    {
        bool called = false;
        
        function = [&called]() { called = true; };
        function();

        CHECK(called);
    }
}

} // namespace NOS