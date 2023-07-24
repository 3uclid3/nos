#pragma once

#include <string/string-view.hpp>
#include <utility/source-location.hpp>

namespace NOS {

[[noreturn]] void panic(StringView message, SourceLocation location = SourceLocation::current());

} // namespace NOS
