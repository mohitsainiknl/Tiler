#pragma once

#include "glm/glm.hpp"

#include "CameraOrthographic.h"
#include "GraphicsAPI.h"
#include "Shader.h"

#include <memory>

namespace tiler {

	class Renderer {
	public:
		static void sceneBegin(CameraOrthographic& camera);
		static void sceneEnd();

		static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vertexBuffer,
		    const std::shared_ptr<IndexBuffer>& indexBuffer, const glm::mat4& transform = glm::mat4(1.0f));
		inline static GraphicsAPI::Type getType() { return GraphicsAPI::Static::getType(); }

	private:
		struct SceneData {
			glm::mat4 matrixViewProject;
		};

		static SceneData* m_sceneData;
	};
}  // namespace tiler