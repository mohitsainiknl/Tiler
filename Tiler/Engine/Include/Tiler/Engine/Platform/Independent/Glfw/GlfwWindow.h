#pragma once

#include "Tiler/Engine/Core/Window.h"


// Forward Declarations
namespace Tiler {
	class OpenGLRenderContext;
}
struct GLFWwindow;


namespace Tiler {

		class GlfwWindow : public Window {
	public:
		GlfwWindow(const std::string& title, int width, int height);
		~GlfwWindow() override;

		void Update() override;

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
		OpenGLRenderContext* m_Context;

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