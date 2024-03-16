#pragma once

#include <functional>
#include <string>

// Forward Declaration
namespace tiler {
	class Event;
}

namespace tiler {

	class Window {
	public:
		using EventCallback = std::function<void(const Event&)>;

		static Window* create(const std::string& title, int width, int height);

		virtual ~Window(){};

		virtual void onUpdate()                                      = 0;
		virtual int getWidth() const                                 = 0;
		virtual int getHeight() const                                = 0;
		virtual void* getInnerWindow() const                         = 0;
		virtual void setEventCallback(const EventCallback& callback) = 0;
	};
}  // namespace tiler