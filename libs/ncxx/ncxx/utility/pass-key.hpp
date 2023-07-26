#pragma once

namespace NOS {

template<typename T>
class PassKey
{
private:
    friend T;

    // Avoid = default to disallow creation by uniform initialization.
    PassKey()
    {}
};

} // namespace NOS
