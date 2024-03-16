#include "Tiler/Engine/Core/Renderer/Buffer/BufferLayout.h"

#include "Tiler/Engine/Base.h"

namespace tiler {

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case tiler::ShaderDataType::FLOAT:  return 4;
			case tiler::ShaderDataType::FLOAT2: return 4 * 2;
			case tiler::ShaderDataType::FLOAT3: return 4 * 3;
			case tiler::ShaderDataType::FLOAT4: return 4 * 4;
			case tiler::ShaderDataType::INT:    return 4;
			case tiler::ShaderDataType::INT2:   return 4 * 2;
			case tiler::ShaderDataType::INT3:   return 4 * 3;
			case tiler::ShaderDataType::INT4:   return 4 * 4;
			case tiler::ShaderDataType::BOOL:   return 1;
		}

		TL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	static uint32_t ShaderDataTypeCount(ShaderDataType type) {
		switch (type) {
			case tiler::ShaderDataType::FLOAT:  return 1;
			case tiler::ShaderDataType::FLOAT2: return 2;
			case tiler::ShaderDataType::FLOAT3: return 3;
			case tiler::ShaderDataType::FLOAT4: return 4;
			case tiler::ShaderDataType::INT:    return 1;
			case tiler::ShaderDataType::INT2:   return 2;
			case tiler::ShaderDataType::INT3:   return 3;
			case tiler::ShaderDataType::INT4:   return 4;
			case tiler::ShaderDataType::BOOL:   return 1;
		}

		TL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized)
	    : name(name), type(type), size(ShaderDataTypeSize(type)), compCount(ShaderDataTypeCount(type)),
	      normalized(normalized) {
	}

	void BufferLayout::calculateStride() {
		m_stride = 0;
		for (const auto& element : m_elements) {
			m_stride += element.size;
		}
	}
}  // namespace tiler
