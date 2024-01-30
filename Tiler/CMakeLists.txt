
add_library(TilerLibrary SHARED
	"Include/Tiler/Application.h"
	"Include/Tiler/EntryPoint.h"

	"Include/Tiler/Core.h"
	"Include/Tiler/Log.h"
	"Include/Tiler/Window.h"

	"Include/Tiler/Events/Event.h"
	"Include/Tiler/Events/KeyEvent.h"
	"Include/Tiler/Events/MouseEvent.h"
	"Include/Tiler/Events/ApplicationEvent.h"
	"Include/Tiler/Platform/Independent/Glfw/GlfwWindow.h"

	"Source/Log.cpp"
	"Source/Application.cpp"

	"Source/Events/Event.cpp"
	"Source/Events/KeyEvent.cpp"
	"Source/Events/MouseEvent.cpp"
	"Source/Events/ApplicationEvent.cpp"

	"Source/Platform/Independent/Glfw/GlfwWindow.cpp"
)


find_package(spdlog CONFIG REQUIRED)
target_link_libraries(TilerLibrary PRIVATE spdlog::spdlog)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(TilerLibrary PRIVATE glfw)



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
)
