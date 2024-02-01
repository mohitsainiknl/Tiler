#pragma once

#include "Log.h"
#include "KeyCode.h"
#include "MouseButtonCode.h"

#if TL_ENABLE_ASSERTS

#include <limits>
#include <cstdlib>

#define TL_CORE_ASSERT(condition, message)\
    if (!(condition)) { \
        TL_CORE_ERROR("Assertion failed! \n    Message: {0}\n    File: {1}({2})", message, __FILE__, __LINE__); \
        std::abort(); \
    }

#else
#define TL_CORE_ASSERT(condition, message)

#endif // TL_ENABLE_ASSERTS


#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIND_EVENT_FN_CUSTOM(obj, fn) std::bind(&fn, &obj, std::placeholders::_1)
