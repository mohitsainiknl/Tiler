
#include "Tiler/Application.h"

#include "Tiler/Core.h"
#include "Tiler/Window.h"
#include "Tiler/Events/KeyEvent.h"
#include "Tiler/Events/ApplicationEvent.h"


#define BIND_EVENT_FN(name) std::bind(&Application::name, this, std::placeholders::_1)

namespace Tiler {

	Application::Application() {
		Log::init();

		TL_CORE_TRACE("Logs Initialized!");

		m_Window = std::unique_ptr<Window>(Window::Create());

		EventDispatcher& dispacher = m_Window->GetEventDispatcher();
		dispacher.Subscribe(EventType::WINDOW_CLOSE, BIND_EVENT_FN(onWindowClose));
	}

	Application::~Application() {

	}

	Application* CreateApplication();


	void Application::Run() {

		EventDispatcher& dispacher = m_Window->GetEventDispatcher();

		dispacher.Subscribe(EventType::KEY_PRESSED, [](const Event& event) {
			const KeyPressedEvent& keyPressedEvent = static_cast<const KeyPressedEvent&>(event);
			int keyCode = keyPressedEvent.GetKeyCode();
			TL_CORE_DEBUG("Key pressed: {0}", keyCode);
		});

		while (m_Running) {
			m_Window->OnUpdate();
		}
	}

	void Application::onWindowClose(const Event& e)
	{
		m_Running = false;
	}

} // namespace Tiler


