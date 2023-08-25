#include <ncxx/container/details/array-base.hpp>

#include <catch2/catch_test_macros.hpp>
#include <ncxx/memory/address-of.hpp>
#include <ncxx/memory/allocator/null-allocator.hpp>
#include <ncxx/memory/allocator/stack-allocator.hpp>

namespace NOS::Details {

namespace {
template<typename T, typename TAllocator, typename TSize>
class TestArrayBase : public ArrayBase<T, TAllocator, TSize>
{
    using Base = ArrayBase<T, TAllocator, TSize>;

public:
    static constexpr size_t InplaceSize = 10;

    constexpr TestArrayBase() { setBuffer(addressOf(inplace)); }

    constexpr void setBuffer(void* buffer) { Base::_buffer = buffer; }

    using Base::getAddressOfFirstInplace;
    using Base::isInplaceBuffer;

    alignas(T) byte_t inplace[InplaceSize];
};
} // namespace

TEST_CASE("ArrayBase", "[Array]")
{
    int buffer[10];

    SECTION("TSize = u32_t")
    {
        TestArrayBase<int, Memory::NullAllocator, u64_t> array;

        CHECK(array.getAddressOfFirstInplace() == addressOf(array.inplace));
        CHECK(array.isInplaceBuffer());

        // simulate allocation
        array.setBuffer(addressOf(buffer));

        CHECK(array.getAddressOfFirstInplace() != addressOf(buffer));
        CHECK_FALSE(array.isInplaceBuffer());
    }

    SECTION("TSize = u32_t")
    {
        TestArrayBase<int, Memory::NullAllocator, u64_t> array;

        CHECK(array.getAddressOfFirstInplace() == addressOf(array.inplace));
        CHECK(array.isInplaceBuffer());

        // simulate allocation
        array.setBuffer(addressOf(buffer));

        CHECK(array.getAddressOfFirstInplace() != addressOf(buffer));
        CHECK_FALSE(array.isInplaceBuffer());
    }

    SECTION("Non-empty allocator")
    {
        TestArrayBase<int, Memory::StackAllocator<256>, u64_t> array;

        CHECK(array.getAddressOfFirstInplace() == addressOf(array.inplace));
        CHECK(array.isInplaceBuffer());

        // simulate allocation
        array.setBuffer(addressOf(buffer));

        CHECK(array.getAddressOfFirstInplace() != addressOf(buffer));
        CHECK_FALSE(array.isInplaceBuffer());
    }
}

} // namespace NOS::Details