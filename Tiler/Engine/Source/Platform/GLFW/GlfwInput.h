#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "Tiler/Engine/Core/Input.h"

namespace tiler {

	class GlfwInput : public Input {
	private:
		bool isKeyPressedImpl(int keycode) override;
		bool isMouseButtonPressedImpl(int button) override;

		std::pair<float, float> getMousePosImpl() override;
		float getMouseXImpl() override;
		float getMouseYImpl() override;

		std::pair<int, int> getWindowSizeImpl();
		int getWindowWidthImpl();
		int getWindowHeightImpl();
	};
}  // namespace tiler