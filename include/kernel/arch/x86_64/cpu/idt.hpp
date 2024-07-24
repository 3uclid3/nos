#pragma once

#include <array>
#include <functional>

#include <arch/x86_64/cpu/cpu_registers.hpp>
#include <kdef.hpp>

namespace nos::x86_64 {

struct cpu_registers;

class idt
{
public:
    struct NOS_PACKED ptr
    {
        std::uint16_t limit;
        std::uint64_t base;
    };

    struct NOS_PACKED entry
    {
        std::uint16_t offset1;
        std::uint16_t selector;
        std::uint8_t ist;
        std::uint8_t type_attr;
        std::uint16_t offset2;
        std::uint32_t offset3;
        std::uint32_t zero;

        void setup(void* new_isr_ptr, std::uint8_t new_type_attr = 0x8E, std::uint8_t new_ist = 0);
    };

    using handler = std::function<void(const cpu_registers&)>;

public:
    void init();
    void load();

    void dispatch_interrupt(const cpu_registers& registers);

private:
    void dispatch_exception(const cpu_registers& registers);
    void dispatch_handler(const cpu_registers& registers);
    void dispatch_unknown(const cpu_registers& registers);

private:
    std::array<entry, 256> _entries{};
    std::array<handler, 256> _handlers{};
};

} // namespace nos::x86_64