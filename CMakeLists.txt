
cmake_minimum_required (VERSION 3.16)


project (
	"Tiler"
	VERSION 0.1
	DESCRIPTION "A Graphics Engine"
	LANGUAGES CXX
)


set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binary)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binary)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binary)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)



add_subdirectory(Tiler/Engine)
add_subdirectory(Tiler/EngineSandbox)


# Note: This is temporary, as the location of the executable depends on the compiler type and build configuration.
file(COPY ${CMAKE_SOURCE_DIR}/Assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
file(COPY ${CMAKE_SOURCE_DIR}/Assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
