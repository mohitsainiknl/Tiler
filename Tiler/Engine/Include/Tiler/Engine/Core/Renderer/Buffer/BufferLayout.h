#pragma once

#include <cstdint>
#include <string>
#include <vector>


namespace Tiler {

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
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t CompCount;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);
	};

	class BufferLayout {
	public:
		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
			CalculateStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

	private:
		void CalculateStride();

		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

}