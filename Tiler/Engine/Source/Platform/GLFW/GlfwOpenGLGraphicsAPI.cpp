#include "GlfwOpenGLGraphicsAPI.h"

#include "Tiler/Engine/Base.h"
#include "glfw_base.h"

namespace tiler {

	GlfwOpenGLGraphicsAPI::GlfwOpenGLGraphicsAPI(GLFWwindow* windowContext)
	    : m_glfwWindow(windowContext), m_vSync(false) {
		TL_CORE_ASSERT(windowContext, "WindowContext is not initialized!");
	}

	void GlfwOpenGLGraphicsAPI::initialize() {
		glfwMakeContextCurrent(m_glfwWindow);
		const int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TL_CORE_ASSERT(success, "Failed to initialize GLAD!");

		TL_CORE_TRACE("OpenGL Info:\n"
		              "    Vendor   : {0}\n"
		              "    Renderer : {1}\n"
		              "    Version  : {2}",
		    (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER),
		    (const char*)glGetString(GL_VERSION));

		TL_OPENGL_DEBUG_OUTPUT;
	}

	void GlfwOpenGLGraphicsAPI::shutdown() {
	}

	void GlfwOpenGLGraphicsAPI::setClearColor(const glm::vec4& color, bool do_clear) {
		glClearColor(color.r, color.g, color.b, color.a);
		if (do_clear) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}

	void GlfwOpenGLGraphicsAPI::nextFrame(bool do_clear) {
		glfwSwapBuffers(m_glfwWindow);
		if (do_clear) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}

	void GlfwOpenGLGraphicsAPI::setVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}

		m_vSync = enabled;
	}

	bool GlfwOpenGLGraphicsAPI::isVSync() const {
		return m_vSync;
	}

}  // namespace tiler