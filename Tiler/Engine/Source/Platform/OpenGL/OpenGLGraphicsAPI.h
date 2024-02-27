#pragma once

#include "Tiler/Engine/Core/Renderer/GraphicsAPI.h"


namespace Tiler {

	class OpenGLGraphicsAPI : public GraphicsAPI {
	public:
		OpenGLGraphicsAPI() = default;
		~OpenGLGraphicsAPI() override = default;

		void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer) override;
	};
}