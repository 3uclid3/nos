#include <cxx/cxa.hpp>
#include <kdef.hpp>
#include <kernel.hpp>

HEDLEY_C_DECL void _start()
{
    using namespace nos;

    kernel k;

    k.serial_init();
    k.early_init();

    cxa::init();

    k.init();
    k.main();
}
