#pragma once

#include <ncxx/preprocessor/concat.hpp>

#define NOS_UNIQUEVAR(prefix) NOS_CONCAT(prefix, __LINE__)
