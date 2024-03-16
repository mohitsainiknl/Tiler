#include "Tiler/Engine/Core/Events/MouseEvent.h"

namespace tiler {

	tiler::MouseMovedEvent::MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {
	}

	std::string tiler::MouseMovedEvent::toString() const {
		const auto x = std::to_string(m_mouseX);
		const auto y = std::to_string(m_mouseY);
		return "MouseMovedEvent: " + x + ", " + y;
	}

	tiler::MouseScrolledEvent::MouseScrolledEvent(float offsetX, float offsetY)
	    : m_offsetX(offsetX), m_offsetY(offsetY) {
	}

	std::string tiler::MouseScrolledEvent::toString() const {
		const auto offsetX = std::to_string(m_offsetX);
		const auto offsetY = std::to_string(m_offsetY);
		return "MouseScrolledEvent: " + offsetX + ", " + offsetY;
	}

	tiler::MouseButtonEvent::MouseButtonEvent(int button) : m_button(button) {
	}

	tiler::MouseButtonPressedEvent::MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {
	}

	std::string tiler::MouseButtonPressedEvent::toString() const {
		const auto button = std::to_string(m_button);
		return "MouseButtonPressedEvent: " + button;
	}

	tiler::MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {
	}

	std::string tiler::MouseButtonReleasedEvent::toString() const {
		const auto button = std::to_string(m_button);
		return "MouseButtonReleasedEvent: " + button;
	}

}  // namespace tiler
