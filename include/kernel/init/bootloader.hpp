#pragma once

#include <limine.h>

namespace nos::limine {

const volatile limine_memmap_request& get_memmap_request();
const volatile limine_hhdm_request& get_hhdm_request();

} // namespace nos::limine