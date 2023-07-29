#pragma once

#include <ncxx/concept/enumeration.hpp>
#include <ncxx/type-trait/underlying-type.hpp>

namespace NOS {

constexpr auto toUnderlyingType(Enumeration auto value)
{
    return static_cast<UnderlyingTypeT<decltype(value)>>(value);
}

} // namespace NOS