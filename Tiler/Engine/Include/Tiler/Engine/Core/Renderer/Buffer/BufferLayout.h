#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace tiler {

	enum class ShaderDataType {
		NONE = 0,
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		INT,
		INT2,
		INT3,
		INT4,
		BOOL
	};

	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t compCount;
		bool normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);
	};

	class BufferLayout {
	public:
		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements) { calculateStride(); }

		inline uint32_t getStride() const { return m_stride; }
		inline const std::vector<BufferElement>& getElements() const { return m_elements; }

	private:
		void calculateStride();

		std::vector<BufferElement> m_elements;
		uint32_t m_stride = 0;
	};

}  // namespace tiler