#pragma once

#ifdef NOS_DEBUG

#define NOS_IF_DEBUG(trueValue, elseValue) trueValue
#define NOS_DEBUG_ONLY(...) __VA__ARGS__

#elif NOS_RELEASE

#define NOS_IF_RELEASE(trueValue, elseValue) trueValue
#define NOS_RELEASE_ONLY(...) __VA__ARGS__

#else
#error "Unknown build type"
#endif

#ifndef NOS_IF_DEBUG
#define NOS_IF_DEBUG(trueValue, elseValue) elseValue
#endif

#ifndef NOS_DEBUG_ONLY
#define NOS_DEBUG_ONLY(...) 
#endif

#ifndef NOS_IF_RELEASE
#define NOS_IF_RELEASE(trueValue, elseValue) elseValue
#endif

#ifndef NOS_RELEASE_ONLY
#define NOS_RELEASE_ONLY(...)
#endif
