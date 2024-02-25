
add_library(TilerEngine_shared STATIC
	"Include/Tiler/Engine.h"

	"Include/Tiler/Engine/Base.h"
	"Include/Tiler/Engine/EntryPoint.h"
	"Include/Tiler/Engine/KeyCode.h"
	"Include/Tiler/Engine/MouseButtonCode.h"

	"Include/Tiler/Engine/Core/Application.h"
	"Include/Tiler/Engine/Core/Log.h"

	"Include/Tiler/Engine/Core/Window.h"
	"Include/Tiler/Engine/Core/Layer.h"
	"Include/Tiler/Engine/Core/LayerStack.h"
	"Include/Tiler/Engine/Core/Input.h"
	"Include/Tiler/Engine/Core/Timestep.h"

	"Include/Tiler/Engine/Core/Events/Event.h"
	"Include/Tiler/Engine/Core/Events/KeyEvent.h"
	"Include/Tiler/Engine/Core/Events/MouseEvent.h"
	"Include/Tiler/Engine/Core/Events/ApplicationEvent.h"

	"Include/Tiler/Engine/Core/ImGui/ImGuiLayer.h"
	
	"Include/Tiler/Engine/Core/Renderer/Renderer.h"
	"Include/Tiler/Engine/Core/Renderer/RendererAPI.h"
	"Include/Tiler/Engine/Core/Renderer/RenderCommand.h"
	"Include/Tiler/Engine/Core/Renderer/RenderContext.h"
	"Include/Tiler/Engine/Core/Renderer/Shader.h"
	"Include/Tiler/Engine/Core/Renderer/VertexArray.h"
	"Include/Tiler/Engine/Core/Renderer/CameraOrthographic.h"

	"Include/Tiler/Engine/Core/Renderer/Buffer/BufferLayout.h"
	"Include/Tiler/Engine/Core/Renderer/Buffer/IndexBuffer.h"
	"Include/Tiler/Engine/Core/Renderer/Buffer/VertexBuffer.h"

	"Source/Platform/GLFW/GlfwWindow.h"
	"Source/Platform/GLFW/GlfwInput.h"

	"Source/Platform/GLFW/GlfwWindow.cpp"
	"Source/Platform/GLFW/GlfwInput.cpp"
	"Source/Platform/OpenGL/OpenGLRenderContext.cpp"
	"Source/Platform/OpenGL/OpenGLRendererAPI.cpp"
	"Source/Platform/OpenGL/OpenGLVertexArray.cpp"

	"Source/Platform/OpenGL/OpenGLRenderContext.h"
	"Source/Platform/OpenGL/OpenGLRendererAPI.h"
	"Source/Platform/OpenGL/OpenGLVertexArray.h"
	"Source/Platform/OpenGL/Buffer/OpenGLIndexBuffer.h"
	"Source/Platform/OpenGL/Buffer/OpenGLIndexBuffer.cpp"
	"Source/Platform/OpenGL/Buffer/OpenGLVertexBuffer.h"
	"Source/Platform/OpenGL/Buffer/OpenGLVertexBuffer.cpp"

	"Source/Core/Log.cpp"
	"Source/Core/Application.cpp"
	"Source/Core/Layer.cpp"
	"Source/Core/LayerStack.cpp"

	"Source/Core/Events/Event.cpp"
	"Source/Core/Events/KeyEvent.cpp"
	"Source/Core/Events/MouseEvent.cpp"
	"Source/Core/Events/ApplicationEvent.cpp"

	"Source/Core/ImGui/ImGuiLayer.cpp"

	"Source/Core/Renderer/Renderer.cpp"
	"Source/Core/Renderer/RendererAPI.cpp"
	"Source/Core/Renderer/RenderCommand.cpp"
	"Source/Core/Renderer/Shader.cpp"
	"Source/Core/Renderer/VertexArray.cpp"
	"Source/Core/Renderer/CameraOrthographic.cpp"

	"Source/Core/Renderer/Buffer/IndexBuffer.cpp"
	"Source/Core/Renderer/Buffer/VertexBuffer.cpp"
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


