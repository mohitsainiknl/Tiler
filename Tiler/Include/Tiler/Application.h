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

	private:
		void onWindowClose(const Event& event);

		std::unique_ptr<Window> m_Window;
		EventDispatcher m_EventDispatcher;
		LayerStack m_LayerStack;
		bool m_Running;
	};

	Application* CreateApplication();
}


