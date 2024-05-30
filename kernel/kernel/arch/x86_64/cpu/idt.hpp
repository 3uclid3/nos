#pragma once

#include <kernel/arch/x86_64/cpu/cpu-registers.hpp>
#include <kernel/def.hpp>
#include <nxx/container/static-array.hpp>

namespace nos::x86_64 {

class idt
{
public:
    struct NOS_PACKED ptr
    {
        u16_t limit;
        u64_t base;
    };

    struct NOS_PACKED entry
    {
        u16_t offset1;
        u16_t selector;
        u8_t ist;
        u8_t type_attr;
        u16_t offset2;
        u32_t offset3;
        u32_t zero;

        void setup(void* new_isr_ptr, uint8_t new_type_attr = 0x8E, uint8_t new_ist = 0);
    };

public:
    void init();

private:
    static_array<entry, 256> _entries{};
    ptr _ptr{};
};

} // namespace nos::x86_64
