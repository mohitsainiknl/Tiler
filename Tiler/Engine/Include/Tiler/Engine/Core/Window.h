#pragma once

#include <string>


namespace Tiler {

	class Window {
	public:
		static Window* Create(const std::string& title, int width, int height);

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual void* GetNativeWindow() const = 0;

		virtual double GetAbsoluteTime() const = 0;
	};

}
