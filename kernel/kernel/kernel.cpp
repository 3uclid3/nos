#include <kernel/kernel.hpp>

namespace nos {

kernel::kernel()
{
    early_init();
    init();
}

void kernel::run()
{
}

void kernel::early_init()
{
    _arch.early_init();
}

void kernel::init()
{
    _arch.init();
}

} // namespace nos