
add_executable(TilerEngineSandbox
	"Source/Sandbox.cpp"
)


target_link_libraries(TilerEngineSandbox PRIVATE TilerEngine_shared)


set_target_properties(TilerEngineSandbox PROPERTIES
    OUTPUT_NAME "TilerEngineSandbox"
)
