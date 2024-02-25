#include "Tiler/Engine/Core/Events/MouseEvent.h"


namespace Tiler {

	Tiler::MouseMovedEvent::MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {

	}

	std::string Tiler::MouseMovedEvent::ToString() const {
		const auto x = std::to_string(m_MouseX);
		const auto y = std::to_string(m_MouseY);
		return "MouseMovedEvent: " + x + ", " + y;
	}


	Tiler::MouseScrolledEvent::MouseScrolledEvent(float offsetX, float offsetY) : m_OffsetX(offsetX), m_OffsetY(offsetY) {

	}

	std::string Tiler::MouseScrolledEvent::ToString() const {
		const auto offsetX = std::to_string(m_OffsetX);
		const auto offsetY = std::to_string(m_OffsetY);
		return "MouseScrolledEvent: " + offsetX + ", " + offsetY;
	}



	Tiler::MouseButtonEvent::MouseButtonEvent(int button) : m_Button(button) {

	}

	Tiler::MouseButtonPressedEvent::MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {
	}

	std::string Tiler::MouseButtonPressedEvent::ToString() const {
		const auto button = std::to_string(m_Button);
		return "MouseButtonPressedEvent: " + button;
	}

	Tiler::MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {

	}

	std::string Tiler::MouseButtonReleasedEvent::ToString() const {
		const auto button = std::to_string(m_Button);
		return "MouseButtonReleasedEvent: " + button;
	}

} // namespace Tiler
