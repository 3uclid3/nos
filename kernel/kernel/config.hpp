#pragma once

#include <ncxx/preprocessor/build-type.hpp>

#ifndef NOS_ENABLE_SERIAL_PORT_TESTING
#define NOS_ENABLE_SERIAL_PORT_TESTING NOS_IF_DEBUG(1, 0)
#endif
