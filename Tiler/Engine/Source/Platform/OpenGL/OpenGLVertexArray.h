#pragma once

#include "Tiler/Engine/Core/Renderer/Buffer/BufferLayout.h"

namespace Tiler {

	class OpenGLVertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const;
		void Unbind() const;

		void SetupLayout(const BufferLayout& layout);

	private:
		uint32_t m_RendererID;
	};

}