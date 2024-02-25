#pragma once

#include "Tiler/Engine/Base.h"
#include "BufferLayout.h"

namespace Tiler {

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);

	protected:
		VertexBuffer() = default;
	};

}