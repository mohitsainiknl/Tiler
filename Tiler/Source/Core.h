#pragma once

#include "Log.h"


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
