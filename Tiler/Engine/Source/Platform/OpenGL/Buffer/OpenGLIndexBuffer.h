#pragma once

#include "Tiler/Engine/Core/Renderer/Buffer/IndexBuffer.h"


namespace Tiler {

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		uint32_t GetCount() const override { return m_Count; };

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}