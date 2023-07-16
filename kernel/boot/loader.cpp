#include <boot/loader.hpp>

#include <limine.h>

namespace nos::boot::loader {

namespace {

volatile limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0,
    .response = nullptr};

} // namespace

bool is_ready()
{
    return framebuffer_request.response != nullptr && 
           framebuffer_request.response->framebuffer_count > 0;
}

limine_framebuffer_request& get_framebuffer_request()
{
    return const_cast<limine_framebuffer_request&>(framebuffer_request);
}

} // namespace nos::boot::loader
