#include "Tiler/Renderer/VertexArray.h"

#include "Tiler/Core.h"
#include "Tiler/Renderer/Renderer.h"
#include "Tiler/Platform/Independent/OpenGL/OpenGLVertexArray.h"

namespace Tiler {

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE:    TL_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); break;
			case RendererAPI::API::OPENGL:  return new OpenGLVertexArray();
		}

		TL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}