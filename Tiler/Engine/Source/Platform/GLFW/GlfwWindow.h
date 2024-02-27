#pragma once

#include "glfw_base.h"

#include "Tiler/Engine/Core/Window.h"



namespace Tiler {

	class GlfwWindow : public Window {
	public:
		GlfwWindow(const std::string& title, int width, int height);
		~GlfwWindow() override;

		void OnUpdate() override;

		inline int GetWidth() const override { return m_Data.Width; }
		inline int GetHeight() const override { return m_Data.Height; }
		inline void* GetInnerWindow() const override { return m_InnerWindow; }
		inline void SetEventCallback(const EventCallback& callback) { m_Data.Callback = callback; };

	private:
		virtual void Init(const std::string& title, int width, int height);
		virtual void Shutdown();

	private:
		GLFWwindow* m_InnerWindow;

		struct WindowData {
			std::string Title = "";
			int Width = 1;
			int Height = 1;
			EventCallback Callback;
		};
		WindowData m_Data;
	};
}