#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Platform/OpenGL/opengl_base.h"

#if TL_ENABLE_OPENGL_DEBUGGING

#	include "Platform/OpenGL/opengl_debugging.h"

#	define TL_GLFW_OPENGL_DEBUG_CONTEXT	 glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true)

#	define TL_OPENGL_DEBUG_OUTPUT                                                                 \
        TL_CORE_TRACE("Enabling OpenGL Debug Output...");                                         \
        int flags;                                                                                \
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);                                                  \
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {                                                  \
            glEnable(GL_DEBUG_OUTPUT);                                                            \
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);                                                \
            glDebugMessageCallback(opengl_debug_callback, nullptr);                               \
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE); \
        }

#else
#	define TL_GLFW_OPENGL_DEBUG_CONTEXT
#	define TL_OPENGL_DEBUG_OUTPUT
#endif

