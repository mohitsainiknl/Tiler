#pragma once

#include "Tiler/Engine/Core/Renderer/Buffer/BufferLayout.h"
#include "Tiler/Engine/Core/Renderer/Buffer/VertexBuffer.h"


namespace Tiler {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		const BufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

}