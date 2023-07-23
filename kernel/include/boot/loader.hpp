#pragma once

struct limine_framebuffer_request;

namespace NOS::Boot::Loader {

[[nodiscard]] bool isReady();

[[nodiscard]] limine_framebuffer_request& getFramebufferRequest();

} // namespace N::boot::loader
