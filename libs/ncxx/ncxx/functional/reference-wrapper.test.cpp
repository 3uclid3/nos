#include <ncxx/functional/reference-wrapper.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/basic-types.hpp>
#include <ncxx/utility/move.hpp>

namespace NOS {

TEST_CASE("ReferenceWrapper", "[functional]")
{
    int value = 3;

    SECTION("ref")
    {
        ReferenceWrapper<int> rw = ref(value);

        CHECK(rw.get() == value);
    }

    SECTION("ref from ref")
    {
        ReferenceWrapper<int> rw = ref(ref(value));

        CHECK(rw.get() == value);
    }

    SECTION("cref")
    {
        ReferenceWrapper<const int> rw = cref(value);

        CHECK(rw.get() == value);
    }

    SECTION("cref from ref")
    {
        ReferenceWrapper<const int> rw = cref(ref(value));

        CHECK(rw.get() == value);
    }

    SECTION("cref from cref")
    {
        ReferenceWrapper<const int> rw = cref(cref(value));

        CHECK(rw.get() == value);
    }

    SECTION("moveable")
    {
        ReferenceWrapper<int> a = ref(value);
        ReferenceWrapper<int> b = move(a);

        CHECK(b.get() == value);
    }
}

} // namespace NOS
