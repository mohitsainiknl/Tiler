#----------------------------------------------------------------------------------------------
# The Tiler Engine is the core component of the project, serving as the main graphics engine.
#----------------------------------------------------------------------------------------------


# library based on object files: compiles the sources only once
add_library(TilerLibrary_object OBJECT

# ROOT
	"Include/Tiler/Engine.h"
	"Include/Tiler/Engine/EntryPoint.h"


# CORE
    "Include/Tiler/Engine/Core/Application.h"
    "Source/Core/Application.cpp"

)





# shared libraries need PIC to work correctly in a multi-process environment.
set_property(TARGET TilerLibrary_object PROPERTY POSITION_INDEPENDENT_CODE True)

# tiler support both shared and static libraries, built from the same object files
add_library(TilerLibrary_shared SHARED $<TARGET_OBJECTS:TilerLibrary_object>)
add_library(TilerLibrary_static STATIC $<TARGET_OBJECTS:TilerLibrary_object>)






# include directories for all libraries
target_include_directories(TilerLibrary_object
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)
target_include_directories(TilerLibrary_shared
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)
target_include_directories(TilerLibrary_static
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)






if(TL_DEV_MODE)
    target_compile_definitions(TilerLibrary_object PRIVATE TL_ENABLE_ASSERTS)
    target_compile_definitions(TilerLibrary_shared PRIVATE TL_ENABLE_ASSERTS)
    target_compile_definitions(TilerLibrary_static PRIVATE TL_ENABLE_ASSERTS)
endif()






set_target_properties(TilerLibrary_object PROPERTIES
    OUTPUT_NAME "TilerEngine_object"
)
set_target_properties(TilerLibrary_shared PROPERTIES
    OUTPUT_NAME "TilerEngine_shared"
)
set_target_properties(TilerLibrary_static PROPERTIES
    OUTPUT_NAME "TilerEngine_static"
)

