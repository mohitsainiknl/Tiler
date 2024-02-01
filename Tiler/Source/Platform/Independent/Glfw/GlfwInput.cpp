#include "Tiler/Platform/Independent/Glfw/GlfwInput.h"

#include "GLFW/glfw3.h"

#include "Tiler/Application.h"
#include "Tiler/Window.h"


#define NATIVE_WINDOW() static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow())

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
		auto window = NATIVE_WINDOW();
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}


	bool GlfwInput::IsMouseButtonPressedImpl(int button) {
		auto window = NATIVE_WINDOW();
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}


	std::pair<float, float> GlfwInput::GetMousePosImpl() {
		auto window = NATIVE_WINDOW();
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

}