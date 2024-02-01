#pragma once

#include <GLFW/glfw3.h>

#include "Tiler/Window.h"
#include "Tiler/Events/Event.h"


namespace Tiler {

	class GlfwWindow : public Window {
	public:
		GlfwWindow(const std::string& title, int width, int height);
		~GlfwWindow() override;

		void OnUpdate() override;

		inline int GetWidth() const override { return m_Data.Width; }
		inline int GetHeight() const override { return m_Data.Height; }
		inline void* GetNativeWindow() const override { return m_Window; }
		inline void SetEventCallback(const EventCallback& callback) { m_Data.Callback = callback; };

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const std::string& title, int width, int height);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title = "";
			int Width = 1;
			int Height = 1;
			bool VSync = false;
			EventCallback Callback;
		};
		WindowData m_Data;
	};
}