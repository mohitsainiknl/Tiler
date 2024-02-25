#include "Tiler/Engine/Core/Renderer/RenderCommand.h"

#include "Tiler/Engine/Platform/Independent/OpenGL/OpenGLRendererAPI.h"


namespace Tiler {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}