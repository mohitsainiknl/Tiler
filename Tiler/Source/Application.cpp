
#include "Tiler/Application.h"

#include "Tiler/Core.h"
#include "Tiler/Window.h"
#include "Tiler/Layer.h"
#include "Tiler/Events/KeyEvent.h"
#include "Tiler/Events/MouseEvent.h"
#include "Tiler/Events/ApplicationEvent.h"
#include "Tiler/Input.h"
#include "Tiler/ImGui/ImGuiLayer.h"


namespace Tiler {

	Application* CreateApplication();

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		Log::init();
		TL_CORE_TRACE("Logs Initialized!");

		TL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		Input::Initialize();
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_EventDispatcher = EventDispatcher();
		m_EventDispatcher.Subscribe(EventType::WINDOW_CLOSE, BIND_EVENT_FN(Application::onWindowClose));
		m_EventDispatcher.Subscribe(BIND_EVENT_FN_CUSTOM(m_LayerStack, LayerStack::OnEvent));
	}

	Application::~Application() {
		Input::Distroy();
	}

	void Application::OnEvent(const Event& event) {
		m_EventDispatcher.Dispatch(event);
	}



	void Application::Run() {

		m_EventDispatcher.Subscribe(EventType::KEY_PRESSED, [](const Event& event) {
			const KeyPressedEvent& keyPressedEvent = static_cast<const KeyPressedEvent&>(event);
			int keyCode = keyPressedEvent.GetKeyCode();
			TL_CORE_DEBUG("Key pressed: {0}", (char)keyCode);
		});

		// Frame Rendering Loop
		while (m_Running) {
			m_ImGuiLayer->OnRenderBegin();

			m_LayerStack.RenderLayers();

			m_ImGuiLayer->OnRenderEnd();
			m_Window->Update();
		}
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::onWindowClose(const Event& event) {
		m_Running = false;
	}

} // namespace Tiler


