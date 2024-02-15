
cmake_minimum_required (VERSION 3.16)


project (
	"Tiler"
	VERSION 0.1
	DESCRIPTION "A Graphics Engine"
	LANGUAGES CXX
)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)


add_subdirectory(Tiler/Engine)
add_subdirectory(Tiler/Sandbox)
