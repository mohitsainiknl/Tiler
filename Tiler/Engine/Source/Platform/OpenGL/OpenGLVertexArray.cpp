#include "OpenGLVertexArray.h"

#include "glad/glad.h"

#include "Tiler/Engine/Base.h"



namespace Tiler {

	static GLenum GetOpenGLBaseType(ShaderDataType type) {
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


	void OpenGLVertexArray::SetupLayout(const BufferLayout& layout) {
		const auto& elements = layout.GetElements();
		const uint32_t stride = layout.GetStride();

		uint32_t offset = 0;
		uint32_t index = 0;
		for (const auto& element : elements) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.CompCount,
				GetOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				stride,
				reinterpret_cast<const void*>(offset)
			);
			offset += element.Size;
			index++;
		}
	}

}