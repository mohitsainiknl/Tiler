
add_executable(Tiler
	"HostApplication.cpp"
)

target_link_libraries(Tiler PRIVATE TilerEngine)
