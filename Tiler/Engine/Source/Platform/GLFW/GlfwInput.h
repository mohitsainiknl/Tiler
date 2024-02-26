#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "Tiler/Engine/Core/Input.h"


namespace Tiler {

	class GlfwInput : public Input {
	private:
		bool IsKeyPressedImpl(int keycode) override;
		bool IsMouseButtonPressedImpl(int button) override;

		std::pair<float, float> GetMousePosImpl() override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;

		std::pair<int, int> GetWindowSizeImpl();
		int GetWindowWidthImpl();
		int GetWindowHeightImpl();
	};
}