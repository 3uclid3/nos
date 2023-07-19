#pragma once

#define NOS_UNUSED(var) (void)var

#define NOS_UNREACHABLE __builtin_unreachable

#ifndef NOS_DEFAULT_ALIGNMENT
#define NOS_DEFAULT_ALIGNMENT 16UL
#endif