
add_library(TilerEngine SHARED
	"Tiler.h"
	"Tiler/EntryPoint.h"
	"Tiler/Application.h"
	"Tiler/Application.cpp"
)

target_include_directories(TilerEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(TilerEngine PUBLIC cxx_std_17)