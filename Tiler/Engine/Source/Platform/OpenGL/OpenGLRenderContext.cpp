#include "OpenGLRenderContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Tiler/Engine/Base.h"


namespace Tiler {

	OpenGLRenderContext::OpenGLRenderContext(GLFWwindow* windowContext) : m_WindowContext(windowContext) {
		TL_CORE_ASSERT(windowContext, "WindowContext is not initialized!");
	}


	void OpenGLRenderContext::Initialize() {
		glfwMakeContextCurrent(m_WindowContext);
		const int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TL_CORE_ASSERT(success, "Failed to initialize GLAD!");

		TL_CORE_INFO(
			"OpenGL Info: \n"
			"    Vendor   : {0}\n"
			"    Renderer : {1}\n"
			"    Version  : {2}"
			, (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER), (const char*)glGetString(GL_VERSION)
		);
	}


	void OpenGLRenderContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowContext);
	}

}