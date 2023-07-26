#pragma once

#ifdef NOS_DEBUG

#define NOS_BUILD_DEBUG 1
#define NOS_BUILD_OPTIMIZED 0
#define NOS_BUILD_UNOPTIMIZED 1

#define NOS_IF_DEBUG(debugValue, nonDebugValue) debugValue
#define NOS_IF_NOT_DEBUG(nonDebugValue, debugValue) debugValue

#define NOS_DEBUG_ONLY(...) __VA__ARGS__
#define NOS_NOT_DEBUG_ONLY(...)

#else

#define NOS_BUILD_DEBUG 0

#define NOS_IF_DEBUG(debugValue, nonDebugValue) nonDebugValue
#define NOS_IF_NOT_DEBUG(nonDebugValue, debugValue) nonDebugValue

#define NOS_DEBUG_ONLY(...)
#define NOS_NOT_DEBUG_ONLY(...) __VA__ARGS__

#endif

#ifdef NOS_RELEASE

#define NOS_BUILD_RELEASE 1
#define NOS_BUILD_OPTIMIZED 1
#define NOS_BUILD_UNOPTIMIZED 0

#define NOS_IF_RELEASE(releaseValue, nonReleaseValue) releaseValue
#define NOS_IF_NOT_RELEASE(nonReleaseValue, releaseValue) releaseValue

#define NOS_RELEASE_ONLY(...) __VA__ARGS__
#define NOS_NOT_RELEASE_ONLY(...)

#else

#define NOS_BUILD_RELEASE 0

#define NOS_IF_RELEASE(releaseValue, nonReleaseValue) nonReleaseValue
#define NOS_IF_NOT_RELEASE(nonReleaseValue, releaseValue) nonReleaseValue

#define NOS_RELEASE_ONLY(...)
#define NOS_NOT_RELEASE_ONLY(...) __VA__ARGS__

#endif

#if !NOS_BUILD_DEBUG && !NOS_BUILD_RELEASE
#error Unsupported build type
#endif
