#pragma once

#include "Event.h"


namespace Tiler {

	class KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_KEYBOARD)

	protected:
		KeyEvent(int keyCode);
		int m_KeyCode;
	};


	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, int repeatCount);
		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override;

		EVENT_CLASS_TYPE(KEY_PRESSED)

	private:
		int m_RepeatCount;
	};


	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode, int repeatCount);

		std::string ToString() const override;

		EVENT_CLASS_TYPE(KEY_RELEASED)
	};

} // namespace Tiler

FMT_SPECIALIZATION(Tiler::KeyEvent);
FMT_SPECIALIZATION(Tiler::KeyPressedEvent);
FMT_SPECIALIZATION(Tiler::KeyReleasedEvent);
