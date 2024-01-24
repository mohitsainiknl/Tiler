#include "Application.h"
#include <spdlog/spdlog.h>

extern Tiler::Application* Tiler::CreateApplication();

int main(int argc, char** argv) {
	auto app = Tiler::CreateApplication();
	app->Run();
	delete app;
}

