
add_library(TilerLibrary SHARED
	"Include/Tiler/Application.h"
	"Include/Tiler/EntryPoint.h"
	"Include/Tiler/Log.h"

	"Source/Application.cpp"
)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(TilerLibrary PRIVATE spdlog::spdlog)

target_include_directories(TilerLibrary
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)

set_target_properties(TilerLibrary PROPERTIES
    OUTPUT_NAME "Tiler"
)
