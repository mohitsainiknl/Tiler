
add_library(TilerLibrary SHARED
	"Source/Application.cpp"
)

target_include_directories(TilerLibrary
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)

set_target_properties(TilerLibrary PROPERTIES
    OUTPUT_NAME "Tiler"
)
