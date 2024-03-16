#pragma once

#include "Tiler/Engine/Core/Events/Event.h"
#include "Tiler/Engine/Core/Window.h"

namespace tiler {

	class Application {
	public:
		Application();
		virtual ~Application();

		void onEvent(const Event& event);
		void run();

		void onRender(){};

		inline Window& getWindow() { return *m_window; }
		inline static Application& get() { return *m_instance; }

	private:
		void onWindowClose(const Event& event);

		std::unique_ptr<Window> m_window;
		EventDispatcher m_eventDispatcher;
		bool m_running        = true;
		float m_lastFrameTime = 0.0f;

		static Application* m_instance;
	};

	Application* createApplication();
}  // namespace tiler
