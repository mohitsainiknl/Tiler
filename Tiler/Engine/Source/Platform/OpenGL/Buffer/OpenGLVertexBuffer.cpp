#include "OpenGLVertexBuffer.h"

#include "glad/glad.h"

namespace tiler {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
		glCreateBuffers(1, &m_rendererID);
		bind();  // Binding VertexBuffer
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &m_rendererID);
	}

	void OpenGLVertexBuffer::bind() const {
		m_vertexArray.bind();
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	}

	void OpenGLVertexBuffer::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_vertexArray.unbind();
	}

	void OpenGLVertexBuffer::setLayout(const BufferLayout& layout) {
		TL_CORE_ASSERT(layout.getElements().size(), "Vertex Buffer has no layout!");

		m_vertexArray.bind();
		bind();  // Binding VertexBuffer

		m_vertexArray.setupLayout(layout);
		m_layout = layout;
	}

}  // namespace tiler