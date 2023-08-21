#include <ncxx/memory/construct-at.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/test/object.fake.hpp>

namespace NOS::Memory {

TEST_CASE_METHOD(Fake::ObjectFixture, "constructAt & destroyAt", "[memory]")
{
    StaticArray<u8_t, sizeof(Fake::Object)> buffer;

    Fake::Object* obj = constructAt(static_cast<Fake::Object*>(static_cast<void*>(buffer.data())));

    REQUIRE(Fake::Object::ctorCount == 1);

    CHECK(obj->ctorDefault);

    destroyAt(obj);

    CHECK(Fake::Object::dtorCount == 1);
}

} // namespace NOS::Memory
