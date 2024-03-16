#pragma once

#include "glfw_base.h"

#include "Tiler/Engine/Core/Window.h"

namespace tiler {

	class GlfwWindow : public Window {
	public:
		GlfwWindow(const std::string& title, int width, int height);
		~GlfwWindow() override;

		void onUpdate() override;

		inline int getWidth() const override { return m_data.width; }
		inline int getHeight() const override { return m_data.height; }
		inline void* getInnerWindow() const override { return m_innerWindow; }
		inline void setEventCallback(const EventCallback& callback) { m_data.callback = callback; };

	private:
		virtual void init(const std::string& title, int width, int height);
		virtual void shutdown();

	private:
		GLFWwindow* m_innerWindow;

		struct WindowData {
			std::string title = "";
			int width         = 1;
			int height        = 1;
			EventCallback callback;
		};
		WindowData m_data;
	};
}  // namespace tiler