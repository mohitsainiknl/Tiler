#include "Tiler/Renderer/RenderCommand.h"

#include "Tiler/Platform/Independent/OpenGL/OpenGLRendererAPI.h"


namespace Tiler {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}