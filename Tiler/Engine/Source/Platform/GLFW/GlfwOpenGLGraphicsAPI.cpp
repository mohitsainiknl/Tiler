#include "GlfwOpenGLGraphicsAPI.h"

#include "Tiler/Engine/Base.h"


namespace Tiler {

	GlfwOpenGLGraphicsAPI::GlfwOpenGLGraphicsAPI(GLFWwindow* windowContext) : m_GlfwWindow(windowContext), m_VSync(false) {
		TL_CORE_ASSERT(windowContext, "WindowContext is not initialized!");
	}


	void GlfwOpenGLGraphicsAPI::Initialize() {
		glfwMakeContextCurrent(m_GlfwWindow);
		const int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TL_CORE_ASSERT(success, "Failed to initialize GLAD!");

		TL_CORE_TRACE(
			"OpenGL Info:\n"
			"    Vendor   : {0}\n"
			"    Renderer : {1}\n"
			"    Version  : {2}"
			, (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER), (const char*)glGetString(GL_VERSION)
		);
	}

	void GlfwOpenGLGraphicsAPI::Shutdown() {

	}

	void GlfwOpenGLGraphicsAPI::SetClearColor(const glm::vec4& color, bool do_clear) {
		glClearColor(color.r, color.g, color.b, color.a);
		if (do_clear) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}

	void GlfwOpenGLGraphicsAPI::NextFrame(bool do_clear) {
		glfwSwapBuffers(m_GlfwWindow);
		if (do_clear) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}

	void GlfwOpenGLGraphicsAPI::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_VSync = enabled;
	}

	bool GlfwOpenGLGraphicsAPI::IsVSync() const {
		return m_VSync;
	}

}