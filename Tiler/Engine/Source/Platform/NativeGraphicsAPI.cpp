#include "NativeGraphicsAPI.h"


namespace Tiler {

	GraphicsAPI* GraphicsAPI::ms_Instance = nullptr;
	GraphicsAPI::Type GraphicsAPI::ms_Type = GraphicsAPI::Type::Auto;

	GraphicsAPI* GraphicsAPI::Create(Type type, void* window) {

		ms_Type = (type == GraphicsAPI::Type::Auto) ? DEFAULT_GRAPHICS_API : type;
		ms_Instance = NATIVE_GRAPHICS_API(ms_Type, window);

		return ms_Instance;
	}


	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {

		return NATIVE_VERTEX_BUFFER(vertices, size);
	}


	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {

		return NATIVE_INDEX_BUFFER(indices, count);
	}

}
