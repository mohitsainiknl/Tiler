#pragma once

#include "Event.h"

namespace tiler {

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(int width, int height);

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }

		std::string toString() const override;

		EVENT_CLASS_TYPE(WINDOW_RESIZE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)

	private:
		int m_width, m_height;
	};

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent();

		EVENT_CLASS_TYPE(WINDOW_CLOSE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};

	class AppTickEvent : public Event {
	public:
		AppTickEvent();

		EVENT_CLASS_TYPE(APP_TICK)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};

	class AppUpdateEvent : public Event {
	public:
		AppUpdateEvent();

		EVENT_CLASS_TYPE(APP_UPDATE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};

	class AppRenderEvent : public Event {
	public:
		AppRenderEvent();

		EVENT_CLASS_TYPE(APP_RENDER)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};

}  // namespace tiler

FMT_SPECIALIZATION(tiler::WindowResizeEvent);
FMT_SPECIALIZATION(tiler::WindowCloseEvent);
FMT_SPECIALIZATION(tiler::AppTickEvent);
FMT_SPECIALIZATION(tiler::AppUpdateEvent);
FMT_SPECIALIZATION(tiler::AppRenderEvent);
