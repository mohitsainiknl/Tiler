#pragma once

#include "Tiler/Engine/Core/Renderer/Buffer/BufferLayout.h"
#include "Tiler/Engine/Core/Renderer/Buffer/VertexBuffer.h"

#include "../OpenGLVertexArray.h"

namespace tiler {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer() override;

		void bind() const override;
		void unbind() const override;

		const BufferLayout& getLayout() const override { return m_layout; }
		void setLayout(const BufferLayout& layout) override;

		OpenGLVertexArray getVertexArray() const { return m_vertexArray; }

	private:
		uint32_t m_rendererID;
		BufferLayout m_layout;

		OpenGLVertexArray m_vertexArray;
	};

}  // namespace tiler