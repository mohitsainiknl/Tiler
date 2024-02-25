#include "Tiler/Engine/Core/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"


namespace Tiler {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}