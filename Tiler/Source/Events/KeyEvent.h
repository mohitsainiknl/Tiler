#pragma once

#include "Event.h"


namespace Tiler {

	class KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(int keyCode);
		int m_KeyCode;
	};


	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, unsigned int repeatCount);
		inline unsigned int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override;

		EVENT_CLASS_TYPE(KEY_PRESSED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_KEYBOARD)

	private:
		unsigned int m_RepeatCount;
	};

} // namespace Tiler

FMT_SPECIALIZATION(Tiler::KeyEvent);
FMT_SPECIALIZATION(Tiler::KeyPressedEvent);
