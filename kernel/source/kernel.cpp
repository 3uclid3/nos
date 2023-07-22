#include <kernel.hpp>

#include <limine.h>

#include <arch/arch.hpp>
#include <base-types.hpp>
#include <boot/loader.hpp>
#include <lang/cxxabi.hpp>

namespace NOS {

void Kernel::init()
{
    Lang::CxxAbi::init();
}

void Kernel::run()
{
    limine_framebuffer* framebuffer = Boot::Loader::getFramebufferRequest().response->framebuffers[0];

    // Note: we assume the framebuffer model is RGB with 32-bit pixels.
    for (size_t i = 0; i < 500; i++)
    {
        u32_t* fb_ptr = reinterpret_cast<u32_t*>(framebuffer->address);
        fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
    }
}

} // namespace N
