#include "NativeWindow.h"

namespace tiler {

	Window* Window::create(const std::string& title, int width, int height) {
		return NATIVE_WINDOW(title, width, height);
	}

}  // namespace tiler
