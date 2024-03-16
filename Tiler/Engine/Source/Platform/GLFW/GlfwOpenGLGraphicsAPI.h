#pragma once

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Platform/OpenGL/OpenGLGraphicsAPI.h"

namespace tiler {

	class GlfwOpenGLGraphicsAPI : public OpenGLGraphicsAPI {
	public:
		GlfwOpenGLGraphicsAPI(GLFWwindow* windowContext);
		~GlfwOpenGLGraphicsAPI() override = default;

		void initialize() override;
		void shutdown() override;

		void setClearColor(const glm::vec4& color, bool do_clear) override;
		void nextFrame(bool do_clear) override;
		void setVSync(bool enabled) override;
		bool isVSync() const override;

	private:
		GLFWwindow* m_glfwWindow;
		bool m_vSync;
	};
}  // namespace tiler