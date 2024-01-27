
add_library(TilerLibrary SHARED
	"Include/Tiler/Application.h"
	"Include/Tiler/EntryPoint.h"

	"Source/Log.h"
	"Source/Log.cpp"
	"Source/Application.cpp"
	"Source/Events/Event.h"
	"Source/Events/Event.cpp"
	"Source/Events/KeyEvent.h"
	"Source/Events/KeyEvent.cpp"
	"Source/Events/MouseEvent.h"
	"Source/Events/MouseEvent.cpp"
	"Source/Events/ApplicationEvent.h"
	"Source/Events/ApplicationEvent.cpp"
)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(TilerLibrary PRIVATE spdlog::spdlog)

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
