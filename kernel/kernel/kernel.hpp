#pragma once

#include <kernel/arch/arch.hpp>

namespace NOS {

class Kernel
{
public:
    void initialize();
    void run();

private:
    Arch _arch;
};

} // namespace NOS
