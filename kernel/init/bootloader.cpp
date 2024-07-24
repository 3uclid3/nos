#include <init/bootloader.hpp>

#include <kdef.hpp>

LIMINE_BASE_REVISION(1)

volatile limine_memmap_request nos_memmap_request{
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0,
    .response = nullptr};

volatile limine_hhdm_request nos_hhdm_request{
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0,
    .response = nullptr};

namespace nos::limine {

const volatile limine_memmap_request& get_memmap_request()
{
    return nos_memmap_request;
}

const volatile limine_hhdm_request& get_hhdm_request()
{
    return nos_hhdm_request;
}

} // namespace nos::limine
