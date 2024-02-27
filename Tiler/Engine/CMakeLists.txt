#----------------------------------------------------------------------------------------------
# The Tiler Engine is the core component of the project, serving as the main graphics engine.
#----------------------------------------------------------------------------------------------


add_library(TilerEngine_shared STATIC

# ROOT
	"Include/Tiler/Engine.h"
	"Include/Tiler/Engine/Base.h"
	"Include/Tiler/Engine/EntryPoint.h"
	"Include/Tiler/Engine/KeyCode.h"
	"Include/Tiler/Engine/MouseButtonCode.h"


# CORE
	"Include/Tiler/Engine/Core/Application.h"
	"Include/Tiler/Engine/Core/Log.h"
	"Include/Tiler/Engine/Core/Window.h"
	"Include/Tiler/Engine/Core/Layer.h"
	"Include/Tiler/Engine/Core/LayerStack.h"
	"Include/Tiler/Engine/Core/Input.h"
	"Include/Tiler/Engine/Core/Timestep.h"

	"Source/Core/Application.cpp"
	"Source/Core/Log.cpp"
	"Source/Core/Layer.cpp"
	"Source/Core/LayerStack.cpp"


# CORE EVENTS
	"Include/Tiler/Engine/Core/Events/Event.h"
	"Include/Tiler/Engine/Core/Events/KeyEvent.h"
	"Include/Tiler/Engine/Core/Events/MouseEvent.h"
	"Include/Tiler/Engine/Core/Events/ApplicationEvent.h"

	"Source/Core/Events/Event.cpp"
	"Source/Core/Events/KeyEvent.cpp"
	"Source/Core/Events/MouseEvent.cpp"
	"Source/Core/Events/ApplicationEvent.cpp"


# FILE
	"Include/Tiler/Engine/Core/FileManager/FileLoader.h"
	"Source/Core/FileManager/FileLoader.cpp"


# CORE IMGUI
	"Include/Tiler/Engine/Core/ImGui/ImGuiLayer.h"
	"Source/Core/ImGui/ImGuiLayer.cpp"


# CORE RENDERER
	"Include/Tiler/Engine/Core/Renderer/Renderer.h"
	"Include/Tiler/Engine/Core/Renderer/GraphicsAPI.h"
	"Include/Tiler/Engine/Core/Renderer/Shader.h"
	"Include/Tiler/Engine/Core/Renderer/CameraOrthographic.h"
	"Include/Tiler/Engine/Core/Renderer/Buffer/BufferLayout.h"
	"Include/Tiler/Engine/Core/Renderer/Buffer/IndexBuffer.h"
	"Include/Tiler/Engine/Core/Renderer/Buffer/VertexBuffer.h"

	"Source/Core/Renderer/Renderer.cpp"
	"Source/Core/Renderer/Shader.cpp"
	"Source/Core/Renderer/CameraOrthographic.cpp"
	"Source/Core/Renderer/Buffer/BufferLayout.cpp"


# PLATFORM
	"Source/Platform/NativeWindow.h"
	"Source/Platform/NativeGraphicsAPI.h"

	"Source/Platform/NativeWindow.cpp"
	"Source/Platform/NativeGraphicsAPI.cpp"


# PLATFORM GLFW
	"Source/Platform/GLFW/glfw_base.h"
	
	"Source/Platform/GLFW/GlfwInput.h"
	"Source/Platform/GLFW/GlfwWindow.h"
	"Source/Platform/GLFW/GlfwOpenGLGraphicsAPI.h"

	"Source/Platform/GLFW/GlfwInput.cpp"
	"Source/Platform/GLFW/GlfwWindow.cpp"
	"Source/Platform/GLFW/GlfwOpenGLGraphicsAPI.cpp"


# PLATFORM OPENGL
	"Source/Platform/OpenGL/opengl_base.h"
	"Source/Platform/OpenGL/opengl_debugging.h"
	"Source/Platform/OpenGL/opengl_debugging.cpp"

	"Source/Platform/OpenGL/OpenGLGraphicsAPI.h"
	"Source/Platform/OpenGL/OpenGLVertexArray.h"
	"Source/Platform/OpenGL/Buffer/OpenGLIndexBuffer.h"
	"Source/Platform/OpenGL/Buffer/OpenGLVertexBuffer.h"

	"Source/Platform/OpenGL/OpenGLGraphicsAPI.cpp"
	"Source/Platform/OpenGL/OpenGLVertexArray.cpp"
	"Source/Platform/OpenGL/Buffer/OpenGLIndexBuffer.cpp"
	"Source/Platform/OpenGL/Buffer/OpenGLVertexBuffer.cpp"
)




find_package(spdlog CONFIG REQUIRED)
target_link_libraries(TilerEngine_shared PUBLIC spdlog::spdlog)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(TilerEngine_shared PUBLIC glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(TilerEngine_shared PUBLIC glad::glad)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(TilerEngine_shared PUBLIC imgui::imgui)

find_package(glm CONFIG REQUIRED)
target_link_libraries(TilerEngine_shared PUBLIC glm::glm)




target_include_directories(TilerEngine_shared
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)




set_target_properties(TilerEngine_shared PROPERTIES
    OUTPUT_NAME "TilerEngine_shared"
)


