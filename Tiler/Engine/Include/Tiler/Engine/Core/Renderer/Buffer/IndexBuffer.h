#pragma once

#include "Tiler/Engine/Base.h"

namespace Tiler {

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);

	protected:
		IndexBuffer() = default;
	};

}