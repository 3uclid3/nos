#include <ncxx/memory/unique-ptr.hpp>

#include <catch2/catch_test_macros.hpp>

namespace NOS {

TEST_CASE("UniquePtr object delete on exit scope", "[memory]")
{
    static bool dtorCalled = false;

    struct DtorObject
    {
        ~DtorObject() { dtorCalled = true; }
    };

    {
        UniquePtr<DtorObject> ptr{new DtorObject()};
    }

    CHECK(dtorCalled);
}

TEST_CASE("UniquePtr::release will release ownership of the object", "[memory]")
{
    UniquePtr<u32_t> ptr{new u32_t()};

    u32_t* val = ptr.release();

    CHECK_FALSE(ptr);

    delete val;
}

} // namespace NOS
