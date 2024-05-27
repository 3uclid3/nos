#pragma once

namespace nos::x86_64 {

class cpu
{
public:
    void early_init();
    void init();
};

} // namespace nos::x86_64
