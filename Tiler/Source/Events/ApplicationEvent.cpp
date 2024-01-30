#include "ApplicationEvent.h"


namespace Tiler {

	WindowResizeEvent::WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {

	}

	std::string WindowResizeEvent::ToString() const {
		const auto width = std::to_string(m_Width);
		const auto height = std::to_string(m_Height);
		return "WindowResizeEvent: " + width + ", " + height;
	}

	WindowCloseEvent::WindowCloseEvent() {

	}

	AppTickEvent::AppTickEvent() {

	}

	AppUpdateEvent::AppUpdateEvent() {

	}

	AppRenderEvent::AppRenderEvent() {

	}

} // namespace Tiler
