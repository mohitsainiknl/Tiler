#include "NativeGraphicsAPI.h"

namespace tiler {

	GraphicsAPI* GraphicsAPI::m_instance  = nullptr;
	GraphicsAPI::Type GraphicsAPI::m_type = GraphicsAPI::Type::AUTO;

	GraphicsAPI* GraphicsAPI::create(Type type, void* window) {
		m_type     = (type == GraphicsAPI::Type::AUTO) ? DEFAULT_GRAPHICS_API : type;
		m_instance = NATIVE_GRAPHICS_API(m_type, window);

		return m_instance;
	}

	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size) {
		return NATIVE_VERTEX_BUFFER(vertices, size);
	}

	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count) {
		return NATIVE_INDEX_BUFFER(indices, count);
	}

	Shader* Shader::create(const std::string& vertexSource, const std::string& fragmentSource) {
		return NATIVE_SHADER(vertexSource, fragmentSource);
	}

	Texture* Texture::create(const std::string& filePath) {
		return NATIVE_TEXTURE(filePath);
	}

}  // namespace tiler
