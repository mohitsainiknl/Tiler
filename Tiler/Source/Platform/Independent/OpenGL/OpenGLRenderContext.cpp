#include "Tiler/Platform/Independent/OpenGL/OpenGLRenderContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Tiler/Core.h"


namespace Tiler {

	OpenGLRenderContext::OpenGLRenderContext(GLFWwindow* windowContext) : m_WindowContext(windowContext) {
		TL_CORE_ASSERT(windowContext, "WindowContext is not initialized!");
	}


	void OpenGLRenderContext::Initialize() {
		glfwMakeContextCurrent(m_WindowContext);
		const int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TL_CORE_ASSERT(success, "Failed to initialize GLAD!");
	}


	void OpenGLRenderContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowContext);
	}

}