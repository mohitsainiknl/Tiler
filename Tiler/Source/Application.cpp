
#include "Tiler/Application.h"
#include "Log.h"


namespace Tiler {

	Application::Application() {
		Log::init();
	}

	Application::~Application() {

	}

	Application* CreateApplication();

	void Application::Run() {
		TL_CORE_WARN("Logs Initialized!");
		TL_INFO("Hello Tiler!");
		while (true);
	}
}


