
add_executable(TilerApplication
	"Source/Launcher.cpp"
)

target_link_libraries(TilerApplication PRIVATE TilerEngine_shared)

set_target_properties(TilerApplication PROPERTIES
    OUTPUT_NAME "Tiler"
)
