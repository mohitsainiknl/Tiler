#include "OpenGLVertexArray.h"

#include "glad/glad.h"

#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Renderer/Buffer/VertexBuffer.h"
#include "Tiler/Engine/Core/Renderer/Buffer/IndexBuffer.h"



namespace Tiler {

	static GLenum ShaderDataType_to_OpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
			case Tiler::ShaderDataType::FLOAT:	  return GL_FLOAT;
			case Tiler::ShaderDataType::FLOAT2:	  return GL_FLOAT;
			case Tiler::ShaderDataType::FLOAT3:	  return GL_FLOAT;
			case Tiler::ShaderDataType::FLOAT4:	  return GL_FLOAT;
			case Tiler::ShaderDataType::INT:	  return GL_INT;
			case Tiler::ShaderDataType::INT2:	  return GL_INT;
			case Tiler::ShaderDataType::INT3:	  return GL_INT;
			case Tiler::ShaderDataType::INT4:	  return GL_INT;
			case Tiler::ShaderDataType::BOOL:	  return GL_BOOL;
		}

		TL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_RendererID);
	}


	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}


	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}


	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}


	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		TL_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataType_to_OpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}


	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}