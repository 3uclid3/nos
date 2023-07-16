#pragma once

struct limine_framebuffer_request;

namespace nos::boot::loader {

[[nodiscard]] bool is_ready();

[[nodiscard]] limine_framebuffer_request& get_framebuffer_request();

} // namespace nos::boot::loader
