
#include "Launcher.h"




int main(int argc, char** argv) {
	auto app = Tiler::CreateApplication();
	app->Run();
	delete app;
}
