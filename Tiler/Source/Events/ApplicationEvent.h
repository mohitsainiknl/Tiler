#pragma once

#include "Event.h"


namespace Tiler {

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height);

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override;

		EVENT_CLASS_TYPE(WINDOW_RESIZE)
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)

	private:
		unsigned int m_Width, m_Height;
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

} // namespace Tiler

FMT_SPECIALIZATION(Tiler::WindowResizeEvent);
FMT_SPECIALIZATION(Tiler::WindowCloseEvent);
FMT_SPECIALIZATION(Tiler::AppTickEvent);
FMT_SPECIALIZATION(Tiler::AppUpdateEvent);
FMT_SPECIALIZATION(Tiler::AppRenderEvent);
