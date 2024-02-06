
add_library(TilerLibrary STATIC
	"Include/Tiler/Application.h"
	"Include/Tiler/EntryPoint.h"

	"Include/Tiler/Tiler.h"
	"Include/Tiler/Core.h"
	"Include/Tiler/Log.h"
	"Include/Tiler/KeyCode.h"
	"Include/Tiler/MouseButtonCode.h"

	"Include/Tiler/Window.h"
	"Include/Tiler/Layer.h"
	"Include/Tiler/LayerStack.h"
	"Include/Tiler/Input.h"
	"Include/Tiler/Timestep.h"

	"Include/Tiler/Events/Event.h"
	"Include/Tiler/Events/KeyEvent.h"
	"Include/Tiler/Events/MouseEvent.h"
	"Include/Tiler/Events/ApplicationEvent.h"

	"Include/Tiler/ImGui/ImGuiLayer.h"

	"Include/Tiler/Platform/Independent/Glfw/GlfwWindow.h"
	"Include/Tiler/Platform/Independent/Glfw/GlfwInput.h"
	"Include/Tiler/Platform/Independent/OpenGL/OpenGLRenderContext.h"
	"Include/Tiler/Platform/Independent/OpenGL/OpenGLRendererAPI.h"
	"Include/Tiler/Platform/Independent/OpenGL/OpenGLBuffer.h"
	"Include/Tiler/Platform/Independent/OpenGL/OpenGLVertexArray.h"
	
	"Include/Tiler/Renderer/Renderer.h"
	"Include/Tiler/Renderer/RendererAPI.h"
	"Include/Tiler/Renderer/RenderCommand.h"
	"Include/Tiler/Renderer/RenderContext.h"
	"Include/Tiler/Renderer/Buffer.h"
	"Include/Tiler/Renderer/Shader.h"
	"Include/Tiler/Renderer/VertexArray.h"
	"Include/Tiler/Renderer/CameraOrthographic.h"

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
target_link_libraries(TilerLibrary PUBLIC spdlog::spdlog)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(TilerLibrary PUBLIC glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(TilerLibrary PUBLIC glad::glad)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(TilerLibrary PUBLIC imgui::imgui)

find_package(glm CONFIG REQUIRED)
target_link_libraries(TilerLibrary PUBLIC glm::glm)



target_include_directories(TilerLibrary
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)



set(PCH_FILES "tiler_pch.h" "tiler_pch.cpp")
target_sources(TilerLibrary PRIVATE ${PCH_FILES})
target_precompile_headers(TilerLibrary PRIVATE ${PCH_FILES})



set_target_properties(TilerLibrary PROPERTIES
    OUTPUT_NAME "Tiler"
)

target_compile_definitions(TilerLibrary
	PRIVATE
		$<$<CONFIG:Debug>:TL_ENABLE_ASSERTS>
		GLFW_INCLUDE_NONE
)
