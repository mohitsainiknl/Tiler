#pragma once

#include "Event.h"


namespace Tiler {

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y);

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override;

		EVENT_CLASS_TYPE(MOUSE_MOVED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE)

	private:
		float m_MouseX, m_MouseY;
	};


	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float offsetX, float offsetY);

		std::string ToString() const override;

		EVENT_CLASS_TYPE(MOUSE_SCROLLED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE)

	private:
		float m_OffsetX, m_OffsetY;
	};


	class MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_MOUSE_BUTTON)

	protected:
		MouseButtonEvent(int button);
		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button);

		std::string ToString() const override;

		EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button);

		std::string ToString() const override;

		EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED)
	};

} // namespace Tiler

FMT_SPECIALIZATION(Tiler::MouseMovedEvent);
FMT_SPECIALIZATION(Tiler::MouseScrolledEvent);
FMT_SPECIALIZATION(Tiler::MouseButtonEvent);
FMT_SPECIALIZATION(Tiler::MouseButtonPressedEvent);
FMT_SPECIALIZATION(Tiler::MouseButtonReleasedEvent);
