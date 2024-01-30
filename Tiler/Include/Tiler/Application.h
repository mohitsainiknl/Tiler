#pragma once

#include <memory>

// Forward Declaration
namespace Tiler {
	class Window;
	class Event;
}

namespace Tiler {

	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		void onWindowClose(const Event& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running;
	};

	Application* CreateApplication();
}


