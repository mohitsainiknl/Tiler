
add_executable(TilerApplication
	"Source/Launcher.h"
	"Source/Launcher.cpp"
	"Source/Main.cpp"
)

target_link_libraries(TilerApplication PRIVATE TilerLibrary)

set_target_properties(TilerApplication PROPERTIES
    OUTPUT_NAME "Tiler"
)
