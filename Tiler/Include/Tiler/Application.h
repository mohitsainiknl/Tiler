#pragma once

#include "Events/Event.h"

#include <memory>

// Forward Declaration
namespace Tiler {
	class Window;
}

namespace Tiler {

	class Application {
	public:
		Application();
		virtual ~Application();

		void OnEvent(const Event& event);

		void Run();
	private:
		void onWindowClose(const Event& event);

		std::unique_ptr<Window> m_Window;
		EventDispatcher m_EventDispatcher;
		bool m_Running;
	};

	Application* CreateApplication();
}


