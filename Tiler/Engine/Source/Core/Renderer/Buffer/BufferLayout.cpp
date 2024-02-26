#include "Tiler/Engine/Core/Renderer/Buffer/BufferLayout.h"

#include "Tiler/Engine/Base.h"

namespace Tiler {

	static uint32_t _ShaderDataTypeSize(ShaderDataType type) {
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

	static uint32_t _ShaderDataTypeCount(ShaderDataType type) {
		switch (type)
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

	BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized)
		: Name(name), Type(type), Size(_ShaderDataTypeSize(type)), CompCount(_ShaderDataTypeCount(type)), Normalized(normalized) {

	}

	void BufferLayout::CalculateStride() {
		m_Stride = 0;
		for (const auto& element : m_Elements) {
			m_Stride += element.Size;
		}
	}
}
