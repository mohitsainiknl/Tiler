#----------------------------------------------------------------------------------
# The Sandbox serves as a playground or experimental environment for developers
# to explore and experiment with the capabilities of the Tiler Engine.
#----------------------------------------------------------------------------------

add_executable(TilerSandbox 
	"Source/Sandbox.cpp"
)


target_link_libraries(TilerSandbox PRIVATE TilerLibrary_shared)


set_target_properties(TilerSandbox PROPERTIES
	OUTPUT_NAME "TilerSandbox"
)
