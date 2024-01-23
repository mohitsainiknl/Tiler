
#include "Tiler/Application.h"
#include "Tiler/Log.h"


namespace Tiler {

	Application::Application() {

	}

	Application::~Application() {

	}

	Application* CreateApplication();

	void Application::Run() {
		Log::GetCoreLogger()->info("Logs Initialized!");
		Log::GetClientLogger()->info("Hello Tiler!");
		while (true);
	}
}


