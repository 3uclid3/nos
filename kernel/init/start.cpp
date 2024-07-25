#include <cxx/cxa.hpp>
#include <init/kernel.hpp>
#include <kdef.hpp>

C_DECL void _start()
{
    using namespace nos;

    kernel k;

    k.serial_init();
    k.early_init();

    cxa::init();

    k.init();
    k.main();
}
