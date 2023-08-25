#include <ncxx/memory/tagged-ptr.hpp>

#include <catch2/catch_test_macros.hpp>

namespace NOS {

TEST_CASE("TaggedPtr ctor", "[memory]")
{
    constexpr size_t bitsA = 0x1;
    constexpr size_t bitsB = 0x3;

    size_t valueA;
    size_t valueB;

    const TaggedPtr<size_t> constTaggedPtr(&valueA, bitsA);
    TaggedPtr<size_t> taggedPtr(&valueA, bitsA);

    CHECK(constTaggedPtr.ptr() == &valueA);
    CHECK(taggedPtr.ptr() == &valueA);

    CHECK(constTaggedPtr.bits() == bitsA);
    CHECK(taggedPtr.bits() == bitsA);

    taggedPtr = &valueB;
    taggedPtr = bitsB;

    CHECK(taggedPtr.ptr() == &valueB);
    CHECK(taggedPtr.bits() == bitsB);

    taggedPtr.set(&valueA, bitsA);

    CHECK(taggedPtr.ptr() == &valueA);
    CHECK(taggedPtr.bits() == bitsA);
}

} // namespace NOS
