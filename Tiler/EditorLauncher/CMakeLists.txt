#----------------------------------------------------------------------------------
# The Sandbox serves as a playground or experimental environment for developers
# to explore and experiment with the capabilities of the Tiler Engine.
#----------------------------------------------------------------------------------

add_executable(TilerEditor_launcher 
	"Source/Launcher.cpp"
)


target_link_libraries(TilerEditor_launcher PRIVATE TilerEditor_static)


set_target_properties(TilerEditor_launcher PROPERTIES
	OUTPUT_NAME "TilerEditor_launcher"
)
