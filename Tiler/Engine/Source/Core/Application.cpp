
#include "Tiler/Engine/Core/Application.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Events/ApplicationEvent.h"
#include "Tiler/Engine/Core/Events/KeyEvent.h"
#include "Tiler/Engine/Core/Events/MouseEvent.h"
#include "Tiler/Engine/Core/ImGuiOverlay.h"
#include "Tiler/Engine/Core/Input.h"
#include "Tiler/Engine/Core/Timestep.h"

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

		ImGuiOverlay::init();

		m_eventDispatcher = EventDispatcher();
		m_eventDispatcher.subscribe(EventType::WINDOW_CLOSE, BIND_EVENT_FN(Application::onWindowClose));
		// m_eventDispatcher.subscribe(BIND_EVENT_FN_CUSTOM(m_imGuiOverlay, ImGuiOverlay::onEvent));
	}

	Application::~Application() {
		ImGuiOverlay::shutdown();

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

			ImGuiOverlay::onRenderBegin();
			this->onRender();
			ImGuiOverlay::onRenderEnd();

			m_window->onUpdate();
			GraphicsAPI::Static::nextFrame();
		}
	}

	void Application::onWindowClose(const Event& event) {
		m_running = false;
	}

}  // namespace tiler
