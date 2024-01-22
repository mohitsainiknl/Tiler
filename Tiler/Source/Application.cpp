
#include "Tiler/Application.h"

#include <iostream>

namespace Tiler {

	Application::Application() {

	}

	Application::~Application() {

	}

	extern Application* CreateApplication();

	void Application::Run() {
		std::cout << "Hello Tiler!" << std::endl;
		while (true);
	}
}


