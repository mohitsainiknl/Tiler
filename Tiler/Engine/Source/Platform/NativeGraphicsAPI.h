#pragma once

#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Renderer/GraphicsAPI.h"
#include "Tiler/Engine/Core/Renderer/Buffer/IndexBuffer.h"
#include "Tiler/Engine/Core/Renderer/Buffer/VertexBuffer.h"

#include "NativeWindow.h"

#include <memory>


#define DEFAULT_GRAPHICS_API	Tiler::GraphicsAPI::Type::OpenGL	// OS Default Graphics API Type


#ifdef TL_WINDOW_GLFW
#	include "GLFW/GlfwOpenGLGraphicsAPI.h"
#   include "OpenGL/OpenGLVertexArray.h"
#   include "OpenGL/Buffer/OpenGLIndexBuffer.h"
#   include "OpenGL/Buffer/OpenGLVertexBuffer.h"

namespace Tiler {

    GraphicsAPI* NATIVE_GRAPHICS_API(GraphicsAPI::Type type, void* window) {
        GLFWwindow* glfw_window = static_cast<GLFWwindow*>(window);
        switch (type) {
            case GraphicsAPI::Type::OpenGL: return new GlfwOpenGLGraphicsAPI(glfw_window);
        }

        TL_CORE_ASSERT(false, "Unknown Graphics API!");
        return nullptr;
    }

    VertexBuffer* NATIVE_VERTEX_BUFFER(float* vertices, uint32_t size) {
        switch (GraphicsAPI::Static::GetType()) {
            case GraphicsAPI::Type::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }
        TL_CORE_ASSERT(false, "Unknown Graphics API!");
        return nullptr;
    }

    IndexBuffer* NATIVE_INDEX_BUFFER(uint32_t* indices, uint32_t count) {
        switch (GraphicsAPI::Static::GetType()) {
            case GraphicsAPI::Type::OpenGL: return new OpenGLIndexBuffer(indices, count);
        }
        TL_CORE_ASSERT(false, "Unknown Graphics API!");
        return nullptr;
    }
}
#else
#	define NATIVE_GRAPHICS_API(type, window)     nullptr;
#	define NATIVE_VERTEX_ARRAY()                 nullptr;
#	define NATIVE_VERTEX_BUFFER(vertices, size)  nullptr;
#	define NATIVE_INDEX_BUFFER(indices, count)   nullptr;
#endif
