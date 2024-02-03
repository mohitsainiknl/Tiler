#pragma once

#include "Tiler/Renderer/RenderContext.h"


// Forward Declaration
struct GLFWwindow;


namespace Tiler {

	class OpenGLRenderContext : public RenderContext {
	public:
		OpenGLRenderContext(GLFWwindow* windowContext);
		~OpenGLRenderContext() = default;

		void Initialize() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowContext;
	};
}