#pragma once


#if !defined(NDEBUG) || defined(TL_DEV_MODE)
#   define TL_ENABLE_DEV_LOGS true
#   define TL_ENABLE_ASSERT_BREAKS true
#endif



#include "KeyCode.h"
#include "MouseButtonCode.h"

#include "Core/Log.h"
#include <cstdlib>



#ifdef TL_ENABLE_ASSERT_BREAKS
#   define ASSERT_BREAK() std::abort()
#else
#   define ASSERT_BREAK()
#endif // TL_ENABLE_ASSERT_BREAKS



#define TL_CORE_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            TL_CORE_ERROR("Assertion failed! \n    File: {0}({1})\n    Message: {2}", __FILE__, __LINE__, message); \
            ASSERT_BREAK(); \
        } \
    } while(false)



#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIND_EVENT_FN_CUSTOM(obj, fn) std::bind(&fn, &obj, std::placeholders::_1)
