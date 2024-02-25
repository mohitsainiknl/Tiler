
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
	"Include/Tiler/Engine/Core/Renderer/Buffer.h"
	"Include/Tiler/Engine/Core/Renderer/Shader.h"
	"Include/Tiler/Engine/Core/Renderer/VertexArray.h"
	"Include/Tiler/Engine/Core/Renderer/CameraOrthographic.h"

	"Include/Tiler/Engine/Platform/Independent/Glfw/GlfwWindow.h"
	"Include/Tiler/Engine/Platform/Independent/Glfw/GlfwInput.h"
	"Include/Tiler/Engine/Platform/Independent/OpenGL/OpenGLRenderContext.h"
	"Include/Tiler/Engine/Platform/Independent/OpenGL/OpenGLRendererAPI.h"
	"Include/Tiler/Engine/Platform/Independent/OpenGL/OpenGLBuffer.h"
	"Include/Tiler/Engine/Platform/Independent/OpenGL/OpenGLVertexArray.h"

	"Source/Log.cpp"
	"Source/Application.cpp"
	"Source/Layer.cpp"
	"Source/LayerStack.cpp"

	"Source/Events/Event.cpp"
	"Source/Events/KeyEvent.cpp"
	"Source/Events/MouseEvent.cpp"
	"Source/Events/ApplicationEvent.cpp"

	"Source/Platform/Independent/Glfw/GlfwWindow.cpp"
	"Source/Platform/Independent/Glfw/GlfwInput.cpp"
	"Source/Platform/Independent/OpenGL/OpenGLRenderContext.cpp"
	"Source/Platform/Independent/OpenGL/OpenGLRendererAPI.cpp"
	"Source/Platform/Independent/OpenGL/OpenGLBuffer.cpp"
	"Source/Platform/Independent/OpenGL/OpenGLVertexArray.cpp"

	"Source/ImGui/ImGuiLayer.cpp"

	"Source/Renderer/Renderer.cpp"
	"Source/Renderer/RendererAPI.cpp"
	"Source/Renderer/RenderCommand.cpp"
	"Source/Renderer/Buffer.cpp"
	"Source/Renderer/Shader.cpp"
	"Source/Renderer/VertexArray.cpp"
	"Source/Renderer/CameraOrthographic.cpp"
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


