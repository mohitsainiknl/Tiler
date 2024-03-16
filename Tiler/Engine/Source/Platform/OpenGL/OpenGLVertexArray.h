#pragma once

#include "Tiler/Engine/Core/Renderer/Buffer/BufferLayout.h"

namespace tiler {

	class OpenGLVertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void bind() const;
		void unbind() const;

		void setupLayout(const BufferLayout& layout);

	private:
		uint32_t m_rendererID;
	};

}  // namespace tiler