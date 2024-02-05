#pragma once

#include "Tiler/Renderer/RenderCommand.h"


namespace Tiler {

	class Renderer {
	public:
		static void SceneBegin();
		static void SceneEnd();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}