#pragma once

#include "Tiler/Engine/Core/Renderer/Buffer/IndexBuffer.h"

namespace tiler {

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void bind() const override;
		void unbind() const override;

		uint32_t getCount() const override { return m_count; };

	private:
		uint32_t m_rendererID;
		uint32_t m_count;
	};

}  // namespace tiler