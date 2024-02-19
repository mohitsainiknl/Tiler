#pragma once


#if !defined(NDEBUG) || defined(TL_DEV_MODE)
    #define TL_ENABLE_DEV_LOGS 1
    #define TL_ENABLE_ASSERTS 1
#endif




#include "Core/Log.h"




#if TL_ENABLE_ASSERTS

#include <limits>
#include <cstdlib>

#define TL_CORE_ASSERT(condition, message) \
    if (!(condition)) { \
        TL_CORE_ERROR("Assertion failed! \n    Message: {0}\n    File: {1}({2})", message, __FILE__, __LINE__); \
        std::terminate(); \
    }

#else
#define TL_CORE_ASSERT(condition, message)

#endif // TL_ENABLE_ASSERTS
