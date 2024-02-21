#include "Tiler/Engine/Core/Window.h"



#if defined(TL_WINDOW_GLFW)
	#include "GLFW/GLFWindow.h"
	#define NATIVE_WINDOW(title, width, height) new Tiler::GLFWindow(title, width, height);

#elif defined(TL_WINDOW_SDL)
	#include "SDL/SDLWindow.h"
	#define NATIVE_WINDOW(title, width, height) new Tiler::SDLWindow(title, width, height);

#else
	#define NATIVE_WINDOW(title, width, height) nullptr;
#endif



namespace Tiler {

	Window* Window::Create(const std::string& title, int width, int height) {

		return NATIVE_WINDOW(title, width, height);
	}

}
