#include "KeyEvent.h"


namespace Tiler {

	KeyEvent::KeyEvent(int keyCode) : m_KeyCode(keyCode) {

	}

	KeyPressedEvent::KeyPressedEvent(int keyCode, unsigned int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount) {

	}

	std::string KeyPressedEvent::ToString() const {
		const auto key = std::to_string(m_KeyCode);
		const auto repeats = std::to_string(m_RepeatCount);
		return "KeyPressedEvent: " + key + " (" + repeats + " repeats)";
	}


	KeyReleasedEvent::KeyReleasedEvent(int keyCode, unsigned int repeatCount) : KeyEvent(keyCode){

	}

	std::string KeyReleasedEvent::ToString() const {
		const auto key = std::to_string(m_KeyCode);
		return "KeyReleasedEvent: " + key;
	}

} // namespace Tiler