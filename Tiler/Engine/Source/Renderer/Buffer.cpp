#include "Tiler/Engine/Core/Renderer/Buffer.h"

#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Renderer/Renderer.h"
#include "Tiler/Engine/Platform/Independent/OpenGL/OpenGLBuffer.h"


namespace Tiler {


	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE:    TL_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); break;
			case RendererAPI::API::OPENGL:  return new OpenGLVertexBuffer(vertices, size);
		}

		TL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


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