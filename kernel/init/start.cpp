#include <init/kernel.hpp>
#include <kdef.hpp>

C_DECL void _start()
{
    nos::kernel k;
    k.serial_init();
    k.early_init();
    k.init();
    k.main();
}
