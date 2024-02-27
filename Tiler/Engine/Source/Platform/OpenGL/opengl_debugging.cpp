#include "opengl_debugging.h"

#include <string>


#if TL_ENABLE_OPENGL_DEBUGGING


void APIENTRY opengl_debug_callback(GLenum source,
    GLenum type,
    unsigned int id,
    GLenum severity,
    GLsizei length,
    const char* message,
    const void* userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::string source_name;
    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             source_name = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   source_name = "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: source_name = "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     source_name = "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     source_name = "Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           source_name = "Other"; break;
    }

    std::string type_name;
    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               type_name = "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_name = "Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  type_name = "Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         type_name = "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         type_name = "Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              type_name = "Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          type_name = "Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           type_name = "Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               type_name = "Other"; break;
    }

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH: {
            TL_CORE_ERROR(
                "OpenGL Debug message({0}) : {1}\n"
                "   Source   : {2}\n"
                "   Type     : {3}\n"
                "   Severity : HIGH"
                , id, message, source_name, type_name
            );
            break;
        }
        case GL_DEBUG_SEVERITY_MEDIUM: {
            TL_CORE_WARN(
                "OpenGL Debug message({0}) : {1}\n"
                "   Source   : {2}\n"
                "   Type     : {3}\n"
                "   Severity : MEDIUM"
                , id, message, source_name, type_name
            );
            break;
        }
        case GL_DEBUG_SEVERITY_LOW: {
            TL_CORE_TRACE(
                "OpenGL Debug message({0}) : {1}\n"
                "   Source   : {2}\n"
                "   Type     : {3}\n"
                "   Severity : LOW"
                , id, message, source_name, type_name
            );
            break;
        }
        case GL_DEBUG_SEVERITY_NOTIFICATION: {
            TL_CORE_DEBUG(
                "OpenGL Debug message({0}) : {1}\n"
                "   Source   : {2}\n"
                "   Type     : {3}\n"
                "   Severity : Notification"
                , id, message, source_name, type_name
            );
            break;
        }
    }

}

#endif  // TL_ENABLE_OPENGL_DEBUGGING