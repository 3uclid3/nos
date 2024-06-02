#pragma once

#include <kernel/arch.hpp>
#include <kernel/memory/physical_memory.hpp>

namespace nos {

class kernel
{
public:
    void serial_init();
    void early_init();
    void init();

    void main();

private:
    arch _arch{};

    physical_memory _physical_memory{};
};

} // namespace nos
