#pragma once

#include "Event.h"

namespace tiler {

	class KeyEvent : public Event {
	public:
		inline int getKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_KEYBOARD)

	protected:
		KeyEvent(int keyCode);
		int m_keyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, int repeatCount);
		inline int getRepeatCount() const { return m_repeatCount; }

		std::string toString() const override;

		EVENT_CLASS_TYPE(KEY_PRESSED)

	private:
		int m_repeatCount;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode, int repeatCount);

		std::string toString() const override;

		EVENT_CLASS_TYPE(KEY_RELEASED)
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keyCode);

		std::string toString() const override;

		EVENT_CLASS_TYPE(KEY_TYPED)
	};

}  // namespace tiler

FMT_SPECIALIZATION(tiler::KeyEvent);
FMT_SPECIALIZATION(tiler::KeyPressedEvent);
FMT_SPECIALIZATION(tiler::KeyReleasedEvent);
FMT_SPECIALIZATION(tiler::KeyTypedEvent);
