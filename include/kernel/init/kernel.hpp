#pragma once

#include <arch/arch.hpp>
#include <mm/heap.hpp>
#include <mm/pmm.hpp>

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

    pmm _pmm{};
    heap _heap{};
};

} // namespace nos
