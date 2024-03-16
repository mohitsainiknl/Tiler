#include "OpenGLVertexArray.h"

#include "glad/glad.h"

#include "Tiler/Engine/Base.h"

namespace tiler {

	static GLenum getOpenGLBaseType(ShaderDataType type) {
		switch (type) {
			case tiler::ShaderDataType::FLOAT:  return GL_FLOAT;
			case tiler::ShaderDataType::FLOAT2: return GL_FLOAT;
			case tiler::ShaderDataType::FLOAT3: return GL_FLOAT;
			case tiler::ShaderDataType::FLOAT4: return GL_FLOAT;
			case tiler::ShaderDataType::INT:    return GL_INT;
			case tiler::ShaderDataType::INT2:   return GL_INT;
			case tiler::ShaderDataType::INT3:   return GL_INT;
			case tiler::ShaderDataType::INT4:   return GL_INT;
			case tiler::ShaderDataType::BOOL:   return GL_BOOL;
		}

		TL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_rendererID);
	}

	void OpenGLVertexArray::bind() const {
		glBindVertexArray(m_rendererID);
	}

	void OpenGLVertexArray::unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::setupLayout(const BufferLayout& layout) {
		const auto& elements  = layout.getElements();
		const uint32_t stride = layout.getStride();

		uint32_t offset = 0;
		uint32_t index  = 0;
		for (const auto& element : elements) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.compCount, getOpenGLBaseType(element.type),
			    element.normalized ? GL_TRUE : GL_FALSE, stride, reinterpret_cast<const void*>(offset));
			offset += element.size;
			index++;
		}
	}

}  // namespace tiler