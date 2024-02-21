#pragma once

#include "SDL2/SDL.h"

#include "Tiler/Engine/Core/Window.h"

namespace Tiler {

	class SDLWindow : public Window {
	public:
		SDLWindow(const std::string& title, int width, int height);
		~SDLWindow() override;

		void OnUpdate() override;

		int GetWidth() const override { return m_Width; };
		int GetHeight() const override { return m_Height; };
		void* GetNativeWindow() const override { return m_Window; };

		double GetAbsoluteTime() const override;

	private:
		void Initialize();
		void Shutdown();


		SDL_Window* m_Window;

		double m_ClockFrequency;

		std::string m_Title;
		int m_Width;
		int m_Height;
	};

}