#pragma once

#include "GLFW/glfw3.h"

#include "Tiler/Engine/Core/Window.h"

namespace Tiler {

	class GLFWindow : public Window {
	public:
		GLFWindow(const std::string& title, int width, int height);
		~GLFWindow() override;

		void OnUpdate() override;

		int GetWidth() const override { return m_Width; };
		int GetHeight() const override { return m_Height; };
		void* GetNativeWindow() const override { return m_Window; };

		double GetAbsoluteTime() const override;

	private:
		void Initialize();
		void Shutdown();


		GLFWwindow* m_Window;

		double m_ClockFrequency;

		std::string m_Title;
		int m_Width;
		int m_Height;
	};

}