
#include "Tiler/Engine/Core/Application.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Events/ApplicationEvent.h"
#include "Tiler/Engine/Core/Events/KeyEvent.h"
#include "Tiler/Engine/Core/Events/MouseEvent.h"
#include "Tiler/Engine/Core/ImGui/ImGuiLayer.h"
#include "Tiler/Engine/Core/Input.h"
#include "Tiler/Engine/Core/Layer.h"
#include "Tiler/Engine/Core/Timestep.h"
#include "Tiler/Engine/Core/Window.h"

#include "Tiler/Engine/Core/Renderer/GraphicsAPI.h"

namespace tiler {

	Application* CreateApplication();

	Application* Application::m_instance = nullptr;

	Application::Application() {
		TL_CORE_ASSERT(!m_instance, "Application already exists!");
		m_instance = this;

		m_window = std::unique_ptr<Window>(Window::create("Tiler Engine", 1280, 720));
		Input::initialize();
		m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

		GraphicsAPI::Static::initialize(GraphicsAPI::Type::AUTO, m_window->getInnerWindow());

		m_imGuiLayer = new ImGuiLayer();
		pushOverlay(m_imGuiLayer);

		m_eventDispatcher = EventDispatcher();
		m_eventDispatcher.subscribe(EventType::WINDOW_CLOSE, BIND_EVENT_FN(Application::onWindowClose));
		m_eventDispatcher.subscribe(BIND_EVENT_FN_CUSTOM(m_layerStack, LayerStack::onEvent));
	}

	Application::~Application() {
		GraphicsAPI::Static::shutdown();
		Input::distroy();
	}

	void Application::onEvent(const Event& event) {
		m_eventDispatcher.dispatch(event);
	}

	void Application::run() {
		// Frame Rendering Loop
		while (m_running) {
			float time        = (float)glfwGetTime();
			Timestep timestep = time - m_lastFrameTime;
			m_lastFrameTime   = time;

			m_imGuiLayer->onRenderBegin();

			m_layerStack.renderLayers(timestep);

			m_imGuiLayer->onRenderEnd();
			m_window->onUpdate();
			GraphicsAPI::Static::nextFrame();
		}
	}

	void Application::pushLayer(Layer* layer) {
		m_layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* overlay) {
		m_layerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	void Application::onWindowClose(const Event& event) {
		m_running = false;
	}

}  // namespace tiler
