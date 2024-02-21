#include "Tiler/Engine/Core/Application.h"

#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Window.h"

namespace Tiler {

	void Application::Run() {

		TL_CORE_INFO("Hello Tiler Engine!");
		TL_CORE_ASSERT(true, "This Assertion Never Fails!");

#ifdef TL_ENABLE_ASSERTS
		TL_CORE_INFO("Assertion Enabled!");
#endif

#ifdef TL_ENABLE_DEV_LOGS
		TL_CORE_INFO("Internal Logs Enabled!");
#endif

		Window* window = Window::Create("Tiler Engine", 1280, 720);
		while (true) {
			window->OnUpdate();
		}
		delete window;
	}
}
