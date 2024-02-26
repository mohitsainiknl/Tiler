
#include "Tiler/Engine/Core/Application.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Window.h"
#include "Tiler/Engine/Core/Layer.h"
#include "Tiler/Engine/Core/Events/KeyEvent.h"
#include "Tiler/Engine/Core/Events/MouseEvent.h"
#include "Tiler/Engine/Core/Events/ApplicationEvent.h"
#include "Tiler/Engine/Core/Input.h"
#include "Tiler/Engine/Core/ImGui/ImGuiLayer.h"
#include "Tiler/Engine/Core/Timestep.h"

#include "Tiler/Engine/Core/Renderer/GraphicsAPI.h"


namespace Tiler {

	Application* CreateApplication();

	Application* Application::s_Instance = nullptr;


	Application::Application() {

		TL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create("Tiler Engine", 1280, 720));
		Input::Initialize();
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		GraphicsAPI::Static::Initialize(GraphicsAPI::Type::Auto, m_Window->GetInnerWindow());

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_EventDispatcher = EventDispatcher();
		m_EventDispatcher.Subscribe(EventType::WINDOW_CLOSE, BIND_EVENT_FN(Application::onWindowClose));
		m_EventDispatcher.Subscribe(BIND_EVENT_FN_CUSTOM(m_LayerStack, LayerStack::OnEvent));
	}

	Application::~Application() {
		GraphicsAPI::Static::Shutdown();
		Input::Distroy();
	}

	void Application::OnEvent(const Event& event) {
		m_EventDispatcher.Dispatch(event);
	}



	void Application::Run() {

		// Frame Rendering Loop
		while (m_Running) {
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_ImGuiLayer->OnRenderBegin();

			m_LayerStack.RenderLayers(timestep);

			m_ImGuiLayer->OnRenderEnd();
			m_Window->OnUpdate();
			GraphicsAPI::Static::NextFrame();
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


