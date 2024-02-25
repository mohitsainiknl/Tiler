#pragma once

#include "Tiler/Engine/Base.h"

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

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case Tiler::ShaderDataType::FLOAT:	  return 4;
		case Tiler::ShaderDataType::FLOAT2:	  return 4 * 2;
		case Tiler::ShaderDataType::FLOAT3:	  return 4 * 3;
		case Tiler::ShaderDataType::FLOAT4:	  return 4 * 4;
		case Tiler::ShaderDataType::INT:	  return 4;
		case Tiler::ShaderDataType::INT2:	  return 4 * 2;
		case Tiler::ShaderDataType::INT3:	  return 4 * 3;
		case Tiler::ShaderDataType::INT4:	  return 4 * 4;
		case Tiler::ShaderDataType::BOOL:	  return 1;
		}

		TL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {

		}

		uint32_t GetComponentCount() const {
			switch (Type)
			{
			case Tiler::ShaderDataType::FLOAT:   return 1;
			case Tiler::ShaderDataType::FLOAT2:	 return 2;
			case Tiler::ShaderDataType::FLOAT3:	 return 3;
			case Tiler::ShaderDataType::FLOAT4:	 return 4;
			case Tiler::ShaderDataType::INT:	 return 1;
			case Tiler::ShaderDataType::INT2:	 return 2;
			case Tiler::ShaderDataType::INT3:	 return 3;
			case Tiler::ShaderDataType::INT4:	 return 4;
			case Tiler::ShaderDataType::BOOL:	 return 1;
			}

			TL_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

}