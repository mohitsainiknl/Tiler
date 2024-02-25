#include "Tiler/Engine/Core/Renderer/VertexArray.h"

#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

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