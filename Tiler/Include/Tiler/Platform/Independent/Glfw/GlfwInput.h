#pragma once

#include "Tiler/Input.h"


namespace Tiler {

	class GlfwInput : public Input {
	private:
		bool IsKeyPressedImpl(int keycode) override;
		bool IsMouseButtonPressedImpl(int button) override;
		std::pair<float, float> GetMousePosImpl() override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
	};
}