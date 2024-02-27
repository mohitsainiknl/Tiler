#include "OpenGLVertexBuffer.h"

#include "glad/glad.h"


namespace Tiler {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
		glCreateBuffers(1, &m_RendererID);
		Bind();	// Binding VertexBuffer
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}


	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}


	void OpenGLVertexBuffer::Bind() const {
		m_VertexArray.Bind();
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}


	void OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_VertexArray.Unbind();
	}


	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout) {
		TL_CORE_ASSERT(layout.GetElements().size(), "Vertex Buffer has no layout!");

		m_VertexArray.Bind();
		Bind();	// Binding VertexBuffer

		m_VertexArray.SetupLayout(layout);
		m_Layout = layout;
	}

}