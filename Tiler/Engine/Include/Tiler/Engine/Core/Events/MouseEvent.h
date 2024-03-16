#pragma once

#include "Event.h"

namespace tiler {

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y);

		inline float getX() const { return m_mouseX; }
		inline float getY() const { return m_mouseY; }

		std::string toString() const override;

		EVENT_CLASS_TYPE(MOUSE_MOVED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE)

	private:
		float m_mouseX, m_mouseY;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float offsetX, float offsetY);

		inline float getOffsetX() const { return m_offsetX; }
		inline float getOffsetY() const { return m_offsetY; }

		std::string toString() const override;

		EVENT_CLASS_TYPE(MOUSE_SCROLLED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE)

	private:
		float m_offsetX, m_offsetY;
	};

	class MouseButtonEvent : public Event {
	public:
		inline int getMouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_MOUSE_BUTTON)

	protected:
		MouseButtonEvent(int button);
		int m_button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button);

		std::string toString() const override;

		EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button);

		std::string toString() const override;

		EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED)
	};

}  // namespace tiler

FMT_SPECIALIZATION(tiler::MouseMovedEvent);
FMT_SPECIALIZATION(tiler::MouseScrolledEvent);
FMT_SPECIALIZATION(tiler::MouseButtonEvent);
FMT_SPECIALIZATION(tiler::MouseButtonPressedEvent);
FMT_SPECIALIZATION(tiler::MouseButtonReleasedEvent);
