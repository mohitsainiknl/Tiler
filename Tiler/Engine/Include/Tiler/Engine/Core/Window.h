#pragma once

#include <string>
#include <functional>

// Forward Declaration
namespace Tiler {
	class Event;
}


namespace Tiler {

	class Window {
	public:
		using EventCallback = std::function<void(const Event&)>;

		static Window* Create(const std::string& title, int width, int height);

		virtual ~Window() {};

		virtual void OnUpdate() = 0;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual void* GetInnerWindow() const = 0;
		virtual void SetEventCallback(const EventCallback& callback) = 0;

	};
}