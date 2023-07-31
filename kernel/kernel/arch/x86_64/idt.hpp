#pragma once

#include <ncxx/basic-types.hpp>
#include <ncxx/container/static-array.hpp>
#include <ncxx/preprocessor/packed.hpp>

namespace NOS::X86_64 {

class NOS_PACKED IDT
{
public:
    struct NOS_PACKED Entry
    {
        u16_t offset1;
        u16_t selector;
        u8_t ist;
        u8_t typeAttr;
        u16_t offset2;
        u32_t offset3;
        u32_t zero;

        void set(void* isr_, uint8_t typeAttr_ = 0x8E, uint8_t ist_ = 0);
    };

    using Entries = StaticArray<Entry, 256>;

    struct NOS_PACKED Register
    {
        u16_t limit;
        u64_t base;
    };

public:
    void load();

private:
    [[nodiscard]] Register makeRegister() const;

private:
    Entries _entries;
};

} // namespace NOS::X86_64
