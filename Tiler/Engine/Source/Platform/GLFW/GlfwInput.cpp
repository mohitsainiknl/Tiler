#include "GlfwInput.h"

#include "Tiler/Engine/Core/Application.h"
#include "Tiler/Engine/Core/Window.h"


namespace Tiler {

	Input* Input::s_Instance = nullptr;


	bool Input::Initialize() {
		if (s_Instance)
			return false;
		s_Instance = new GlfwInput();
		return true;
	}

	bool Input::IsInitialized() {
		if (s_Instance)
			return true;
		return false;
	}

	bool Input::Distroy() {
		if (!s_Instance)
			return false;
		delete s_Instance;
		return true;
	}


	bool GlfwInput::IsKeyPressedImpl(int keycode) {
		GLFWwindow* window = glfwGetCurrentContext();
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}


	bool GlfwInput::IsMouseButtonPressedImpl(int button) {
		GLFWwindow* window = glfwGetCurrentContext();
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}


	std::pair<float, float> GlfwInput::GetMousePosImpl() {
		GLFWwindow* window = glfwGetCurrentContext();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return {(float)xpos, (float)ypos};
	}


	float GlfwInput::GetMouseXImpl() {
		auto[x, _] = GetMousePosImpl();
		return x;
	}


	float GlfwInput::GetMouseYImpl() {
		auto [_, y] = GetMousePosImpl();
		return y;
	}


	std::pair<int, int> GlfwInput::GetWindowSizeImpl() {
		GLFWwindow* window = glfwGetCurrentContext();
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		return { width, height };
	}


	int GlfwInput::GetWindowWidthImpl() {
		auto [width, _] = GetWindowSizeImpl();
		return width;
	}


	int GlfwInput::GetWindowHeightImpl() {
		auto [_, height] = GetWindowSizeImpl();
		return height;
	}
}