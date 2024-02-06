#pragma once

#include "Tiler/LayerStack.h"
#include "Tiler/Events/Event.h"


// Forward Declaration
namespace Tiler {
	class Window;
	class Layer;
	class ImGuiLayer;
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
		ImGuiLayer* m_ImGuiLayer;
		EventDispatcher m_EventDispatcher;
		LayerStack m_LayerStack;
		bool m_Running = true;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}


