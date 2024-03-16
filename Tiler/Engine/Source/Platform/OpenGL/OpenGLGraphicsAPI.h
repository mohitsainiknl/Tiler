#pragma once

#include "Tiler/Engine/Core/Renderer/GraphicsAPI.h"

namespace tiler {

	class OpenGLGraphicsAPI : public GraphicsAPI {
	public:
		OpenGLGraphicsAPI()           = default;
		~OpenGLGraphicsAPI() override = default;

		void drawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer,
		    const std::shared_ptr<IndexBuffer>& indexBuffer) override;
	};
}  // namespace tiler