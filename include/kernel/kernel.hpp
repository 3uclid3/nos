#pragma once

#include <arch.hpp>

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
};

} // namespace nos
