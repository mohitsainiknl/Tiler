
cmake_minimum_required (VERSION 3.21)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (
	"Tiler"
	VERSION 0.1
	DESCRIPTION "A Node Based Graphics Engine"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(Tiler)
add_subdirectory(Host)

if (MSVC)
 	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	set_target_properties(${PROJECT_NAME} PROPERTIES
 		WIN32_EXECUTABLE TRUE
		MACOSX_BUNDLE TRUE
	)
endif()

