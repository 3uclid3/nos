#include <boot/loader.hpp>

#include <limine.h>

namespace NOS::Boot::Loader {

namespace {

volatile limine_framebuffer_request framebufferRequest = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0,
    .response = nullptr};

} // namespace

bool isReady()
{
    return framebufferRequest.response != nullptr && framebufferRequest.response->framebuffer_count > 0;
}

limine_framebuffer_request& getFramebufferRequest()
{
    return const_cast<limine_framebuffer_request&>(framebufferRequest);
}

} // namespace NOS::Boot::Loader
