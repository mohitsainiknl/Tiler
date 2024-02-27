#include "Core/Application.h"
#include "Core/Log.h"

extern Tiler::Application* Tiler::CreateApplication();

int main(int argc, char** argv) {
	Tiler::Log::Initialize();

	auto app = Tiler::CreateApplication();
	app->Run();
	delete app;
}

