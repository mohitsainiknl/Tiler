
#include "Tiler/Application.h"

#include "Tiler/Core.h"
#include "Tiler/Window.h"
#include "Tiler/Layer.h"
#include "Tiler/Events/KeyEvent.h"
#include "Tiler/Events/ApplicationEvent.h"


#define BIND_EVENT_FN(name) std::bind(&Application::name, this, std::placeholders::_1)

namespace Tiler {

	Application* CreateApplication();

	Application::Application() {
		Log::init();

		TL_CORE_TRACE("Logs Initialized!");

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_EventDispatcher = EventDispatcher();
		m_EventDispatcher.Subscribe(EventType::WINDOW_CLOSE, BIND_EVENT_FN(onWindowClose));
	}

	Application::~Application() {

	}

	void Application::OnEvent(const Event& event) {
		m_EventDispatcher.Dispatch(event);

		for (auto it = m_LayerStack.end() - 1; it != m_LayerStack.begin(); --it) {
			const auto layer = (*it);
			layer->OnEvent(event);
			if (layer->GetEventHandled())
				break;
		}
	}



	void Application::Run() {

		m_EventDispatcher.Subscribe(EventType::KEY_PRESSED, [](const Event& event) {
			const KeyPressedEvent& keyPressedEvent = static_cast<const KeyPressedEvent&>(event);
			int keyCode = keyPressedEvent.GetKeyCode();
			TL_CORE_DEBUG("Key pressed: {0}", keyCode);
		});

		while (m_Running) {
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::onWindowClose(const Event& event)
	{
		m_Running = false;
	}

} // namespace Tiler


