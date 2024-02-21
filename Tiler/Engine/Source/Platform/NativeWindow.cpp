#include "Tiler/Engine/Core/Window.h"

#include "SDL/SDLWindow.h"



#ifdef TL_WINDOW_NONE
	#define NATIVE_WINDOW(title, width, height) nullptr;
#else
	#define NATIVE_WINDOW(title, width, height) new Tiler::SDLWindow(title, width, height);
#endif



namespace Tiler {

	Window* Window::Create(const std::string& title, int width, int height) {

		return NATIVE_WINDOW(title, width, height);
	}

}
