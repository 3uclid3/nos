#pragma once

#include <ncxx/string/string-view.hpp>
#include <ncxx/utility/source-location.hpp>

namespace NOS {

[[noreturn]] void panic(StringView message, SourceLocation location = SourceLocation::current());

} // namespace NOS
