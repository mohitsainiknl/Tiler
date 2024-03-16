#include "Tiler/Engine/Core/Events/ApplicationEvent.h"

namespace tiler {

	WindowResizeEvent::WindowResizeEvent(int width, int height) : m_width(width), m_height(height) {
	}

	std::string WindowResizeEvent::toString() const {
		const auto width  = std::to_string(m_width);
		const auto height = std::to_string(m_height);
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

}  // namespace tiler
