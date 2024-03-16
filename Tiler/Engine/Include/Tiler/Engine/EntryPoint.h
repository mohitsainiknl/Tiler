#include "Core/Application.h"
#include "Core/Log.h"

extern tiler::Application* tiler::createApplication();

int main(int argc, char** argv) {
	tiler::Log::initialize();

	auto app = tiler::createApplication();
	app->run();
	delete app;
}
