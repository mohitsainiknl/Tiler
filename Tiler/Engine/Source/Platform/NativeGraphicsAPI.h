#pragma once

#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Renderer/Buffer/IndexBuffer.h"
#include "Tiler/Engine/Core/Renderer/Buffer/VertexBuffer.h"
#include "Tiler/Engine/Core/Renderer/GraphicsAPI.h"
#include "Tiler/Engine/Core/Renderer/Shader.h"
#include "Tiler/Engine/Core/Renderer/Texture.h"

#include "NativeWindow.h"

#include <memory>

#define DEFAULT_GRAPHICS_API tiler::GraphicsAPI::Type::OPENGL  // OS Default Graphics API Type

#ifdef TL_WINDOW_GLFW
#include "GLFW/GlfwOpenGLGraphicsAPI.h"
#include "OpenGL/Buffer/OpenGLIndexBuffer.h"
#include "OpenGL/Buffer/OpenGLVertexBuffer.h"
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLTexture.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace tiler {

	GraphicsAPI* NATIVE_GRAPHICS_API(GraphicsAPI::Type type, void* window) {
		GLFWwindow* glfw_window = static_cast<GLFWwindow*>(window);
		switch (type) {
			case GraphicsAPI::Type::OPENGL: return new GlfwOpenGLGraphicsAPI(glfw_window);
		}

		TL_CORE_ASSERT(false, "Unknown Graphics API!");
		return nullptr;
	}

	VertexBuffer* NATIVE_VERTEX_BUFFER(float* vertices, uint32_t size) {
		switch (GraphicsAPI::Static::getType()) {
			case GraphicsAPI::Type::OPENGL: return new OpenGLVertexBuffer(vertices, size);
		}
		TL_CORE_ASSERT(false, "Unknown Graphics API!");
		return nullptr;
	}

	IndexBuffer* NATIVE_INDEX_BUFFER(uint32_t* indices, uint32_t count) {
		switch (GraphicsAPI::Static::getType()) {
			case GraphicsAPI::Type::OPENGL: return new OpenGLIndexBuffer(indices, count);
		}
		TL_CORE_ASSERT(false, "Unknown Graphics API!");
		return nullptr;
	}

	Shader* NATIVE_SHADER(const std::string& vertexSource, const std::string& fragmentSource) {
		switch (GraphicsAPI::Static::getType()) {
			case GraphicsAPI::Type::OPENGL: return new OpenGLShader(vertexSource, fragmentSource);
		}
		TL_CORE_ASSERT(false, "Unknown Graphics API!");
		return nullptr;
	}

	Texture* NATIVE_TEXTURE(const std::string& filePath) {
		switch (GraphicsAPI::Static::getType()) {
			case GraphicsAPI::Type::OPENGL: return new OpenGLTexture(filePath);
		}
		TL_CORE_ASSERT(false, "Unknown Graphics API!");
		return nullptr;
	}
}  // namespace tiler

#else
#define NATIVE_GRAPHICS_API(type, window)    nullptr;
#define NATIVE_VERTEX_ARRAY()                nullptr;
#define NATIVE_VERTEX_BUFFER(vertices, size) nullptr;
#define NATIVE_INDEX_BUFFER(indices, count)  nullptr;
#define NATIVE_SHADER(vs, fs)                nullptr;
#define NATIVE_TEXTURE(filePath)             nullptr;
#endif
