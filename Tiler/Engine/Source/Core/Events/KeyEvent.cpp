#include "Tiler/Engine/Core/Events/KeyEvent.h"

namespace tiler {

	KeyEvent::KeyEvent(int keyCode) : m_keyCode(keyCode) {
	}

	KeyPressedEvent::KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_repeatCount(repeatCount) {
	}

	std::string KeyPressedEvent::toString() const {
		const auto key     = std::to_string(m_keyCode);
		const auto repeats = std::to_string(m_repeatCount);
		return "KeyPressedEvent: " + key + " (" + repeats + " repeats)";
	}

	KeyReleasedEvent::KeyReleasedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode) {
	}

	std::string KeyReleasedEvent::toString() const {
		const auto key = std::to_string(m_keyCode);
		return "KeyReleasedEvent: " + key;
	}

	KeyTypedEvent::KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {
	}

	std::string KeyTypedEvent::toString() const {
		const auto key = std::to_string(m_keyCode);
		return "KeyTypedEvent: " + key;
	}

}  // namespace tiler
