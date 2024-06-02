#pragma once

#include <kernel/arch.hpp>

namespace nos {

class kernel
{
public:
    kernel();

    void run();

private:
    void early_init();
    void init();

    arch _arch{};

    physical_memory _physical_memory{};
};

} // namespace nos
