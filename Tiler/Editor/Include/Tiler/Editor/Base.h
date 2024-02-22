#pragma once

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#pragma warning(pop)


// Client log macros
#define TL_EDIT_TRACE(...)    spdlog::trace(__VA_ARGS__)
#define TL_EDIT_DEBUG(...)    spdlog::debug(__VA_ARGS__)
#define TL_EDIT_INFO(...)     spdlog::info(__VA_ARGS__)
#define TL_EDIT_WARN(...)     spdlog::warn(__VA_ARGS__)
#define TL_EDIT_ERROR(...)    spdlog::error(__VA_ARGS__)
#define TL_EDIT_CRITICAL(...) spdlog::critical(__VA_ARGS__)


#include <cstdlib>

#define TL_EDIT_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            TL_EDIT_ERROR("Assertion failed! \n    File: {0}({1})\n    Message: {2}", __FILE__, __LINE__, message); \
            std::abort(); \
        } \
    } while(false)

