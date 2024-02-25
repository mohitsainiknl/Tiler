#pragma once

#include <memory>

namespace Tiler {

	class Input {
	public:
		static bool Initialize();
		static bool IsInitialized();
		static bool Distroy();

		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		inline static std::pair<int, int> GetWindowSize() { return s_Instance->GetWindowSizeImpl(); }
		inline static int GetWindowWidth() { return s_Instance->GetWindowWidthImpl(); }
		inline static int GetWindowHeight() { return s_Instance->GetWindowHeightImpl(); }

	protected:
		Input() = default;
		virtual ~Input() = default;

		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		virtual std::pair<int, int> GetWindowSizeImpl() = 0;
		virtual int GetWindowWidthImpl() = 0;
		virtual int GetWindowHeightImpl() = 0;

	private:
		static Input* s_Instance;
	};

}

