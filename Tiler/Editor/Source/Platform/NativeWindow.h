#pragma once

#include "GLFW/glfw3.h"

#include <string>

namespace Tiler {

	class NativeWindow {
	public:
		NativeWindow(const std::string& title, int width, int height);
		~NativeWindow();

		void OnUpdate();

		int GetWidth() const { return m_Width; };
		int GetHeight() const { return m_Height; };

		double GetAbsoluteTime() const;

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