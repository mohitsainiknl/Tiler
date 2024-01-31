#pragma once

#include "Tiler/LayerStack.h"
#include "Events/Event.h"

#include <memory>

// Forward Declaration
namespace Tiler {
	class Window;
	class Layer;
}

namespace Tiler {

	class Application {
	public:
		Application();
		virtual ~Application();

		void OnEvent(const Event& event);
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		void onWindowClose(const Event& event);

		std::unique_ptr<Window> m_Window;
		EventDispatcher m_EventDispatcher;
		LayerStack m_LayerStack;
		bool m_Running;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}


