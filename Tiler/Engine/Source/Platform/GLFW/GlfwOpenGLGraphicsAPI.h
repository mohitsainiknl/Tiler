#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Platform/OpenGL/OpenGLGraphicsAPI.h"


namespace Tiler {

	class GlfwOpenGLGraphicsAPI: public OpenGLGraphicsAPI {
	public:
		GlfwOpenGLGraphicsAPI(GLFWwindow* windowContext);
		~GlfwOpenGLGraphicsAPI() override = default;

		void Initialize() override;
		void Shutdown() override;

		void SetClearColor(const glm::vec4& color, bool do_clear) override;
		void NextFrame(bool do_clear) override;
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;


	private:
		GLFWwindow* m_GlfwWindow;
		bool m_VSync;
	};
}