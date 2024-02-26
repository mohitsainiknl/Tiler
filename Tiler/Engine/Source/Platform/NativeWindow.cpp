#include "NativeWindow.h"


namespace Tiler {

	Window* Window::Create(const std::string& title, int width, int height) {

		return NATIVE_WINDOW(title, width, height);
	}

}
