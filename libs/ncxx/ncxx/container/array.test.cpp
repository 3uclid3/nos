#include <catch2/catch_test_macros.hpp>

#include <ncxx/container/array.hpp>
#include <ncxx/container/static-array.hpp>
#include <ncxx/memory/utility.hpp>

namespace NOS {

class FakeAllocator
{
public:
    Memory::Block allocate(size_t size)
    {
        size = Memory::roundToAlignment(size, alignment_t{alignof(u8_t)});

        void* newPointer = static_cast<byte_t*>(_pointer) + size;

        if (newPointer > _buffer.end())
        {
            return Memory::nullblk;
        }

        Memory::Block block{_pointer, size};

        _pointer = newPointer;

        return block;
    }

    void deallocate(Memory::Block block)
    {
        NOS_UNUSED(block);
    }

private:
    static StaticArray<u8_t, 256> _buffer;
    static void* _pointer;
};

StaticArray<u8_t, 256> FakeAllocator::_buffer{};
void* FakeAllocator::_pointer{FakeAllocator::_buffer.data()};

TEST_CASE("Array - ctor")
{
    struct Struct
    {
        u64_t v0;
        u64_t v1;
        u64_t v2;
        u64_t v3;
    };

    InplaceArray<Struct, 32, FakeAllocator> array;

    CHECK_FALSE(array.isAllocated());
}

} // namespace NOS
