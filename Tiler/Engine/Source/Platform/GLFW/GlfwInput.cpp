#include "GlfwInput.h"

#include "Tiler/Engine/Core/Application.h"
#include "Tiler/Engine/Core/Window.h"

namespace tiler {

	Input* Input::m_instance = nullptr;

	bool Input::initialize() {
		if (m_instance) {
			return false;
		}
		m_instance = new GlfwInput();
		return true;
	}

	bool Input::isInitialized() {
		if (m_instance) {
			return true;
		}
		return false;
	}

	bool Input::distroy() {
		if (!m_instance) {
			return false;
		}
		delete m_instance;
		return true;
	}

	bool GlfwInput::isKeyPressedImpl(int keycode) {
		GLFWwindow* window = glfwGetCurrentContext();
		auto state         = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool GlfwInput::isMouseButtonPressedImpl(int button) {
		GLFWwindow* window = glfwGetCurrentContext();
		auto state         = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> GlfwInput::getMousePosImpl() {
		GLFWwindow* window = glfwGetCurrentContext();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return {(float)xpos, (float)ypos};
	}

	float GlfwInput::getMouseXImpl() {
		auto [x, _] = getMousePosImpl();
		return x;
	}

	float GlfwInput::getMouseYImpl() {
		auto [_, y] = getMousePosImpl();
		return y;
	}

	std::pair<int, int> GlfwInput::getWindowSizeImpl() {
		GLFWwindow* window = glfwGetCurrentContext();
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		return {width, height};
	}

	int GlfwInput::getWindowWidthImpl() {
		auto [width, _] = getWindowSizeImpl();
		return width;
	}

	int GlfwInput::getWindowHeightImpl() {
		auto [_, height] = getWindowSizeImpl();
		return height;
	}
}  // namespace tiler