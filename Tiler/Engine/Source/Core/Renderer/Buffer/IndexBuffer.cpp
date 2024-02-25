#include "Tiler/Engine/Core/Renderer/Buffer/IndexBuffer.h"

#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Renderer/Renderer.h"

#include "Platform/OpenGL/Buffer/OpenGLIndexBuffer.h"


namespace Tiler {

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:    TL_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); break;
		case RendererAPI::API::OPENGL:  return new OpenGLIndexBuffer(indices, count);
		}

		TL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}