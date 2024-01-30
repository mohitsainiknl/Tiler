#pragma once


// Forward Declaration
namespace Tiler {
	class EventDispatcher;
}


namespace Tiler {

	class Window {
	public:
		static Window* Create();
		static Window* Create(const std::string& title, int width, int height);

		virtual ~Window() {};

		virtual void OnUpdate() = 0;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual EventDispatcher& GetEventDispatcher() = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
	};
}