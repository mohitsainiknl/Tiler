#pragma once



#ifdef TL_WINDOW_NONE
#	define NATIVE_WINDOW(title, width, height) nullptr;
#else
#	define TL_WINDOW_GLFW	// temporary
#	include "GLFW/GlfwWindow.h"
#	define NATIVE_WINDOW(title, width, height) new Tiler::GlfwWindow(title, width, height);
#endif


