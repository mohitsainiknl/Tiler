#pragma once

#include "BufferLayout.h"
#include "Tiler/Engine/Base.h"

namespace tiler {

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void bind() const   = 0;
		virtual void unbind() const = 0;

		virtual const BufferLayout& getLayout() const      = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* create(float* vertices, uint32_t size);

	protected:
		VertexBuffer() = default;
	};

}  // namespace tiler