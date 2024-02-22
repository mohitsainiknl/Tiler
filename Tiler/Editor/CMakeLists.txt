#----------------------------------------------------------------------------------
# The Sandbox serves as a playground or experimental environment for developers
# to explore and experiment with the capabilities of the Tiler Engine.
#----------------------------------------------------------------------------------

add_library(TilerEditor_static STATIC
	"Include/Tiler/Editor.h"

	"Include/Tiler/Editor/EntryPoint.h"
	"Include/Tiler/Editor/Base.h"

	"Include/Tiler/Editor/Core/Application.h"
	"Include/Tiler/Editor/Core/Layer.h"

	"Source/Core/Application.cpp"

	"Source/Platform/NativeWindow.h"
	"Source/Platform/NativeWindow.cpp"

)

#target_link_libraries(TilerEditor_static PUBLIC TilerLibrary_shared)


find_package(spdlog CONFIG REQUIRED)
target_link_libraries(TilerEditor_static PUBLIC spdlog::spdlog)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(TilerEditor_static PUBLIC glfw)


target_include_directories(TilerEditor_static
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)


set_target_properties(TilerEditor_static PROPERTIES
	OUTPUT_NAME "TilerEditor_static"
)
