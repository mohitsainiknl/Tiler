#pragma once

#include "glad/glad.h"

#include "opengl_base.h"

#if TL_ENABLE_OPENGL_DEBUGGING

void APIENTRY opengl_debug_callback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length,
    const char* message, const void* userParam);

#endif  // TL_ENABLE_OPENGL_DEBUGGING