
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
			TL_WARN("Input Callback...");
		};
		auto fun2 = [](const Event& event) {
			TL_WARN("Keyboard Callback...");
		};
		auto fun3 = [](const Event& event) {
			TL_WARN("Key Pressed Callback...");
		};
		auto fun4 = [](const Event& event) {
			TL_WARN("Unsubscribed Callback...");
		};

		EventDispatcher& ed{ EventDispatcher::getInstance() };
		ed.Subscribe(EventCategory::EVENT_CATEGORY_INPUT, fun1);
		ed.Subscribe(EventCategory::EVENT_CATEGORY_KEYBOARD, fun2);
		ed.Subscribe(EventType::KEY_PRESSED, fun3);
		ed.Subscribe(EventType::KEY_PRESSED, fun4);

		ed.Unsubscribe(EventCategory::EVENT_CATEGORY_KEYBOARD, fun2);
		ed.Unsubscribe(EventType::KEY_PRESSED, fun4);

		KeyPressedEvent e{21, 0};
		TL_WARN("Going to Dispatch " + e.ToString());
		ed.Dispatch(e);

		while (true);
	}

} // namespace Tiler


