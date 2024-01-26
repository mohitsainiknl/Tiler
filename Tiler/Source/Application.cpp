
#include "Tiler/Application.h"
#include "Log.h"
#include "Events/KeyEvent.h"


namespace Tiler {

	Application::Application() {
		Log::init();
	}

	Application::~Application() {

	}

	Application* CreateApplication();

	void Application::Run() {
		TL_INFO("Logs Initialized!");

		auto fun1 = [](const Event& event) {
			TL_WARN("Key Pressed Callback...");
		};
		auto fun2 = [](const Event& event) {
			TL_WARN("Unsubscribed Callback...");
		};

		EventDispatcher& ed{ EventDispatcher::getInstance() };
		ed.Subscribe(EventType::KEY_PRESSED, fun1);
		ed.Subscribe(EventType::KEY_PRESSED, fun2);
		ed.Unsubscribe(EventType::KEY_PRESSED, fun2);

		KeyPressedEvent e{21, 0};
		TL_WARN("Going to Dispatch " + e.ToString());
		ed.Dispatch(e);

		while (true);
	}

} // namespace Tiler


