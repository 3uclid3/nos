#pragma once

struct limine_framebuffer_request;

namespace nos::boot::loader {

[[nodiscard]] bool isReady();

[[nodiscard]] limine_framebuffer_request& getFramebufferRequest();

} // namespace nos::boot::loader
