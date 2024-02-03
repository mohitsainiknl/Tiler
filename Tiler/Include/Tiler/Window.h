#pragma once


// Forward Declaration
namespace Tiler {
	class Event;
}


namespace Tiler {

	class Window {
	public:
		using EventCallback = std::function<void(const Event&)>;

		static Window* Create();
		static Window* Create(const std::string& title, int width, int height);

		virtual ~Window() {};

		virtual void Update() = 0;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual void* GetNativeWindow() const = 0;
		virtual void SetEventCallback(const EventCallback& callback) = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
	};
}