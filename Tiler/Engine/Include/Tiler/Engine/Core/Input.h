#pragma once

#include <memory>

namespace tiler {

	class Input {
	public:
		static bool initialize();
		static bool isInitialized();
		static bool distroy();

		inline static bool isKeyPressed(int keycode) { return m_instance->isKeyPressedImpl(keycode); }
		inline static bool isMouseButtonPressed(int button) { return m_instance->isMouseButtonPressedImpl(button); }

		inline static std::pair<float, float> getMousePos() { return m_instance->getMousePosImpl(); }
		inline static float getMouseX() { return m_instance->getMouseXImpl(); }
		inline static float getMouseY() { return m_instance->getMouseYImpl(); }

		inline static std::pair<int, int> getWindowSize() { return m_instance->getWindowSizeImpl(); }
		inline static int getWindowWidth() { return m_instance->getWindowWidthImpl(); }
		inline static int getWindowHeight() { return m_instance->getWindowHeightImpl(); }

	protected:
		Input()          = default;
		virtual ~Input() = default;

		virtual bool isKeyPressedImpl(int keycode)        = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;

		virtual std::pair<float, float> getMousePosImpl() = 0;
		virtual float getMouseXImpl()                     = 0;
		virtual float getMouseYImpl()                     = 0;

		virtual std::pair<int, int> getWindowSizeImpl() = 0;
		virtual int getWindowWidthImpl()                = 0;
		virtual int getWindowHeightImpl()               = 0;

	private:
		static Input* m_instance;
	};

}  // namespace tiler
